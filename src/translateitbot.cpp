#include "translateitbot.h"

#include <QThread>

TranslateItBot::TranslateItBot(const QString& token, const QString& languageStoragePath, const QString& localFolder)
    : m_state(Error), m_languageStorage(languageStoragePath), m_users(localFolder)
{
    if (m_languageStorage.state() != State::Initialized)
    {
        qCritical() << "LanguageStorage is not initialized!";
        return;
    }
    else
        qInfo() << "LanguageStorage initialized successfully!";
    if (not m_api.start(token))
    {
        qCritical() << "TelegramBotApi did not start!";
        return;
    }
    else
        qInfo() << "TelegramBotApi started successfully!";

    // TODO: add hidden command (stat, shutdown, ...)
    m_api.configureMenuCommands({{"start", "Get new sentence"},
                                 {"settings", "Changle language or difficulty"},
                                 {"help", "Inctructions & contacts"}});

    m_state = State::Initialized;
    m_backupTimer.start();
}

void TranslateItBot::checkUpdates()
{
    if (m_state != State::Initialized) return;

    while (true)
    {
        std::optional<QVector<Telegram::Update::Ptr>> updates = m_api.getUpdates(m_offset);

        if (updates->size())
        {
            for (const Telegram::Update::Ptr& update : updates.value())
            {
                if (update->m_callback_query)
                {
                    qDebug() << "New incomig callback query from" << update->m_callback_query->m_from->m_id;
                    processCallBack(update->m_callback_query);
                }
                else if (update->m_message)
                {
                    qDebug() << "New incomig message from" << update->m_message->m_from->m_id;
                    processMessage(update->m_message);
                }
                m_offset = update->m_update_id + 1;
            }
        }
        else
        {
            // TODO: adjust according to users activity
            QThread::msleep(100);

            if (m_backupTimer.hasExpired(m_backupInterval))
            {
                qDebug() << "Start backup";
                m_users.backup();
                m_backupTimer.restart();
            }
        }
    }
}

bool TranslateItBot::processMessage(Telegram::Message::Ptr message)
{
    auto user = m_users.findOrCreate(message->m_from->m_id);
    if (message->m_text == "/help")
        return processCmd(user, nullptr, "Help");
    else if (message->m_text == "/start")
        return processCmd(user, message, "GetNewSentence");
    else if (message->m_text == "/settings")
        return processCmd(user, nullptr, "SetupUser");

    return false;
}

bool TranslateItBot::processCallBack(Telegram::CallbackQuery::Ptr callback)
{
    QString     cmd = "", arg = "";
    QStringList callbackData = callback->m_data->split(":");
    cmd                      = callbackData[0];
    if (callbackData.size() > 1) arg = callbackData[1];
    auto user = m_users.findOrCreate(callback->m_from->m_id);

    return processCmd(user, callback->m_message, cmd, arg);
}

bool TranslateItBot::processCmd(User::SPtr user, Telegram::Message::Ptr message, QString cmd, QString arg)
{
    if (cmd == "GetNewSentence")
    {
        if (checkAndSetUserSentenceGetter(user) and m_api.sendNewSentence(user))
        {
            return message ? m_api
                                 .editMessageText(message->m_text.value(),
                                                  std::optional(message->m_chat->m_id),
                                                  message->m_message_id)
                                 .has_value()
                           : false;
        }
        else
        {
            if (message)
                m_api.editMessageText(
                    message->m_text.value(), std::optional(message->m_chat->m_id), message->m_message_id);
            m_api.sendMessage(user->id(), "Your settings are incorrect. Please configure it again.").has_value();
            return processCmd(user, nullptr, "SetupUser");
        }
    }
    else if (cmd == "SetupUser")
    {
        // TODO: show current settings?
        QVector<QPair<QString, QString>> languagePairs = m_languageStorage.languages();
        QSet<QString>                    languages;
        for (const auto& pair : languagePairs)
        {
            languages.insert(pair.first);
            languages.insert(pair.second);
        }

        return m_api.sendAvailableLanguages(user, languages);
    }
    else if (cmd == "SetShowLanguage")
    {
        user->setLangShow(arg);

        QVector<QPair<QString, QString>> languagePairs = m_languageStorage.languages();
        QSet<QString>                    languages;
        for (const auto& pair : languagePairs)
        {
            if (pair.first == arg) languages.insert(pair.second);
            if (pair.second == arg) languages.insert(pair.first);
        }

        return m_api.editAvailableLanguages(message, languages);
    }
    else if (cmd == "SetHideLanguage")
    {
        user->setLangHide(arg);

        return m_api.editDifficulty(message);
    }
    else if (cmd == "SetMinDifficulty")
    {
        user->setDifficultyMin(arg.toInt());

        if (user->difficultyMin() != MaxDifficulty)
            return m_api.editDifficulty(message, true, user->difficultyMin());
        else
        {
            user->setDifficultyMax(MaxDifficulty);
            user->setSentenceGetter(nullptr);
            return m_api.confirmSettings(message);
        }
    }
    else if (cmd == "SetMaxDifficulty")
    {
        user->setDifficultyMax(arg.toInt() - 1);
        user->setSentenceGetter(nullptr);
        return m_api.confirmSettings(message);
        // TODO: save sentence id and reset it
    }
    else if (cmd == "Help")
    {
        // TODO: improve help page
        return m_api.sendMessage(user->id(), "For any questions please text @AlexTeos").has_value();
    }

    qWarning() << "Unrecognize command: " << cmd << "from user:" << user->id();

    return false;
}

bool TranslateItBot::checkAndSetUserSentenceGetter(User::SPtr user)
{
    if (user->isSentenceGetterSet()) return true;

    if (checkIsUserConfigured(user))
    {
        std::function<std::optional<SentenceCPtr>(int&)> sentenceGetter = m_languageStorage.sentenceGetter(
            user->langShow(), user->langHide(), user->difficultyMin(), user->difficultyMax());

        user->setReversedSentence(false);
        if (not sentenceGetter)
        {
            sentenceGetter = m_languageStorage.sentenceGetter(
                user->langHide(), user->langShow(), user->difficultyMin(), user->difficultyMax());
            if (not sentenceGetter) return false;
            user->setReversedSentence(true);
        }
        user->setSentenceGetter(sentenceGetter);
        return true;
    }

    return false;
}

bool TranslateItBot::checkIsUserConfigured(User::SPtr user)
{
    // TODO: check if languages exist
    return user->langHide() != "Undefined" and user->langShow() != "Undefined" and
           user->langShow() != user->langHide() and user->difficultyMax() >= user->difficultyMin();
}
