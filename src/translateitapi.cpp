#include "translateitapi.h"

#include <types/message.h>
#include <types/replykeyboardmarkup.h>

constexpr int columnCount = 3;

bool TranslateItApi::sendAvailableLanguages(const User::SPtr user, QSet<QString> languages)
{
    Telegram::InlineKeyboardMarkup::Ptr inlineKeyboardMarkup;
    inlineKeyboardMarkup = Telegram::InlineKeyboardMarkup::Ptr::create();
    inlineKeyboardMarkup->m_inline_keyboard.resize(languages.size() / columnCount + 1);
    int i = 0;
    for (auto iter = languages.constBegin(); iter != languages.constEnd(); ++i, ++iter)
    {
        Telegram::InlineKeyboardButton::Ptr inlineKeyboardButtonSkip;
        inlineKeyboardButtonSkip                  = Telegram::InlineKeyboardButton::Ptr::create();
        inlineKeyboardButtonSkip->m_text          = *iter;
        inlineKeyboardButtonSkip->m_callback_data = "SetShowLanguage:" + *iter;

        inlineKeyboardMarkup->m_inline_keyboard[i / columnCount].push_back(inlineKeyboardButtonSkip);
    }

    return sendMessage(user->id(),
                       "Please choose language you know",
                       std::nullopt,
                       std::nullopt,
                       std::nullopt,
                       std::nullopt,
                       std::nullopt,
                       std::nullopt,
                       std::nullopt,
                       std::optional(inlineKeyboardMarkup))
        .has_value();
}

bool TranslateItApi::editAvailableLanguages(Telegram::Message::Ptr message, QSet<QString> languages)
{
    Telegram::InlineKeyboardMarkup::Ptr inlineKeyboardMarkup;
    inlineKeyboardMarkup = Telegram::InlineKeyboardMarkup::Ptr::create();
    inlineKeyboardMarkup->m_inline_keyboard.resize(languages.size() / columnCount + 1);
    int i = 0;
    for (auto iter = languages.constBegin(); iter != languages.constEnd(); ++i, ++iter)
    {
        Telegram::InlineKeyboardButton::Ptr inlineKeyboardButtonSkip;
        inlineKeyboardButtonSkip                  = Telegram::InlineKeyboardButton::Ptr::create();
        inlineKeyboardButtonSkip->m_text          = *iter;
        inlineKeyboardButtonSkip->m_callback_data = "SetHideLanguage:" + *iter;

        inlineKeyboardMarkup->m_inline_keyboard[i / columnCount].push_back(inlineKeyboardButtonSkip);
    }

    return editMessageText("Please choose language you want to learn",
                           message->m_chat->m_id,
                           message->m_message_id,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           inlineKeyboardMarkup)
        .has_value();
}

bool TranslateItApi::editDifficulty(Telegram::Message::Ptr message, bool max, int minDifficulty)
{
    Telegram::InlineKeyboardMarkup::Ptr inlineKeyboardMarkup;
    inlineKeyboardMarkup = Telegram::InlineKeyboardMarkup::Ptr::create();
    inlineKeyboardMarkup->m_inline_keyboard.resize(1);

    for (int i = minDifficulty; i <= MaxDifficulty; ++i)
    {
        Telegram::InlineKeyboardButton::Ptr inlineKeyboardButtonSkip;
        inlineKeyboardButtonSkip         = Telegram::InlineKeyboardButton::Ptr::create();
        inlineKeyboardButtonSkip->m_text = QString::number(i + 1);
        inlineKeyboardButtonSkip->m_callback_data =
            (max ? "SetMaxDifficulty:" : "SetMinDifficulty:") + QString::number(i);

        inlineKeyboardMarkup->m_inline_keyboard[0].push_back(inlineKeyboardButtonSkip);
    }

    return editMessageText(QStringLiteral("Please choose ") + (max ? "maximum" : "minimal") + " difficulty",
                           message->m_chat->m_id,
                           message->m_message_id,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           inlineKeyboardMarkup)
        .has_value();
}

bool TranslateItApi::confirmSettings(Telegram::Message::Ptr message)
{
    Telegram::InlineKeyboardButton::Ptr inlineKeyboardButtonSkip;
    inlineKeyboardButtonSkip                  = Telegram::InlineKeyboardButton::Ptr::create();
    inlineKeyboardButtonSkip->m_text          = "Get New Sentence";
    inlineKeyboardButtonSkip->m_callback_data = "GetNewSentence";

    Telegram::InlineKeyboardMarkup::Ptr inlineKeyboardMarkup;
    inlineKeyboardMarkup = Telegram::InlineKeyboardMarkup::Ptr::create();
    inlineKeyboardMarkup->m_inline_keyboard.resize(1);
    inlineKeyboardMarkup->m_inline_keyboard[0].push_back(inlineKeyboardButtonSkip);

    return editMessageText(QStringLiteral("The settings have been applied!"),
                           message->m_chat->m_id,
                           message->m_message_id,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           inlineKeyboardMarkup)
        .has_value();
}

bool TranslateItApi::configureMenuCommands(QVector<QPair<QString, QString>> commands)
{
    QVector<Telegram::BotCommand::Ptr> menuCommands;
    menuCommands.resize(commands.size());
    int i = 0;
    for (const auto& command : commands)
    {
        menuCommands[i]                = Telegram::BotCommand::Ptr::create();
        menuCommands[i]->m_command     = command.first;
        menuCommands[i]->m_description = command.second;
        ++i;
    }
    auto result = setMyCommands(menuCommands);
    return result.has_value() && result.value();
}

bool TranslateItApi::sendNewSentence(User::SPtr user)
{
    Telegram::InlineKeyboardButton::Ptr inlineKeyboardButtonSkip;
    inlineKeyboardButtonSkip                  = Telegram::InlineKeyboardButton::Ptr::create();
    inlineKeyboardButtonSkip->m_text          = "New Sentence";
    inlineKeyboardButtonSkip->m_callback_data = "GetNewSentence";

    Telegram::InlineKeyboardMarkup::Ptr inlineKeyboardMarkup;
    inlineKeyboardMarkup = Telegram::InlineKeyboardMarkup::Ptr::create();
    inlineKeyboardMarkup->m_inline_keyboard.resize(1);
    inlineKeyboardMarkup->m_inline_keyboard[0].push_back(inlineKeyboardButtonSkip);

    if (not user->isSentenceGetterSet()) return false;
    auto sentence = user->newSentence();

    if (not user->reversedSentence())
        return sendMessage(user->id(),
                           sentence->first + "\n\n<tg-spoiler>" + sentence->second + "</tg-spoiler>",
                           "HTML",
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::optional(inlineKeyboardMarkup))
            .has_value();
    else
        return sendMessage(user->id(),
                           sentence->second + "\n\n<tg-spoiler>" + sentence->first + "</tg-spoiler>",
                           "HTML",
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::nullopt,
                           std::optional(inlineKeyboardMarkup))
            .has_value();
}
