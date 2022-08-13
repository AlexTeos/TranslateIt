#include "translateitbot.h"

#include <QThread>

TranslateItBot::TranslateItBot(const QString& token, const QString& languageStoragePath)
    : m_state(Error), m_languageStorage(languageStoragePath)
{
    if (m_languageStorage.state() != State::Initialized) return;
    if (not m_api.start(token)) return;

    //TODO: check destruction
    m_user.setLangShow(Language::RU);
    m_user.setLangHide(Language::EN);
    std::function<SentenceCPtr(int&)> sentenceGetter = m_languageStorage.sentenceGetter(
        m_user.langShow(), m_user.langHide(), m_user.difficultyMin(), m_user.difficultyMax());

    if (not sentenceGetter)
    {
        sentenceGetter = m_languageStorage.sentenceGetter(
            m_user.langHide(), m_user.langShow(), m_user.difficultyMin(), m_user.difficultyMax());
        if (not sentenceGetter) return;
        m_user.setReversedSentence(true);
    }
    m_user.setSentenceGetter(sentenceGetter);

    m_state = State::Initialized;
}

void TranslateItBot::start()
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
                    if (sendNewSentence(update->m_callback_query->m_from->m_id))
                    {
                        m_api.editMessageText(update->m_callback_query->m_message->m_text.value(),
                                              update->m_callback_query->m_message->m_chat->m_id,
                                              update->m_callback_query->m_message->m_message_id);
                    }
                }
                else if ((update->m_message) && (update->m_message->m_text == "/start"))
                {
                    sendNewSentence(update->m_message->m_from->m_id);
                }
                m_offset = update->m_update_id + 1;
            }
        }
        else
        {
            QThread::msleep(100);
        }
    }
}

bool TranslateItBot::sendNewSentence(const qint64& id)
{
    Telegram::InlineKeyboardButton::Ptr inlineKeyboardButtonSkip;
    inlineKeyboardButtonSkip                  = Telegram::InlineKeyboardButton::Ptr::create();
    inlineKeyboardButtonSkip->m_text          = "New Sentence";
    inlineKeyboardButtonSkip->m_callback_data = "New";

    Telegram::InlineKeyboardMarkup::Ptr inlineKeyboardMarkup;
    inlineKeyboardMarkup = Telegram::InlineKeyboardMarkup::Ptr::create();
    inlineKeyboardMarkup->m_inline_keyboard.resize(1);
    inlineKeyboardMarkup->m_inline_keyboard[0].push_back(inlineKeyboardButtonSkip);

    SentenceCPtr sentence = m_user.newSentence();

    if (not m_user.reversedSentence())
        return m_api
            .sendMessage(id,
                         sentence->first + "\n\n<tg-spoiler>" + sentence->second + "</tg-spoiler>",
                         "HTML",
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         inlineKeyboardMarkup)
            .has_value();
    else
        return m_api
            .sendMessage(id,
                         sentence->second + "\n\n<tg-spoiler>" + sentence->first + "</tg-spoiler>",
                         "HTML",
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         inlineKeyboardMarkup)
            .has_value();
}
