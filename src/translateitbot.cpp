#include "translateitbot.h"

#include <QThread>

TranslateItBot::TranslateItBot(const QString& token, const QString& tmx) : m_state(Error)
{
    if (not m_sentenceStorage.setXMLFile(tmx)) return;
    if (not m_api.start(token)) return;

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
                    proceedUpdateWithCallback(update->m_callback_query);
                }
                else if (update->m_message)
                {
                    proceedUpdateWithMessage(update->m_message);
                }
                m_offset = update->m_update_id + 1;
            }
        }
        else
        {
            QThread::sleep(1);
        }
    }
}

bool TranslateItBot::proceedUpdateWithCallback(const Telegram::CallbackQuery::Ptr& callback)
{
    if (callback->m_data == "Skip")
    {
        if (replaceSentence(callback->m_message->m_chat->m_id, callback->m_message->m_message_id))
        {
            m_api.answerCallbackQuery(callback->m_id);
            return true;
        }
    }
    else if (callback->m_data == "New")
    {
        if (sendNewSentence(callback->m_from->m_id))
        {
            // Remove inline keyboard
            m_api.editMessageText(callback->m_message->m_text.value(),
                                  callback->m_message->m_chat->m_id,
                                  callback->m_message->m_message_id);
            m_api.answerCallbackQuery(callback->m_id);
            return true;
        }
    }

    return false;
}

bool TranslateItBot::sendNewSentence(const qint64& id)
{
    Telegram::InlineKeyboardMarkup::Ptr inlineKeyboardMarkup;
    Telegram::InlineKeyboardButton::Ptr inlineKeyboardButton;
    inlineKeyboardButton                  = Telegram::InlineKeyboardButton::Ptr::create();
    inlineKeyboardButton->m_text          = "Skip Sentence";
    inlineKeyboardButton->m_callback_data = "Skip";
    inlineKeyboardMarkup                  = Telegram::InlineKeyboardMarkup::Ptr::create();
    inlineKeyboardMarkup->m_inline_keyboard.resize(1);
    inlineKeyboardMarkup->m_inline_keyboard[0].push_back(inlineKeyboardButton);
    m_sentenceStorage.getRandomSentence(m_sentence);

    return m_api
        .sendMessage(id,
                     m_sentence.second,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     inlineKeyboardMarkup)
        .has_value();
}

bool TranslateItBot::sendTranslation(const qint64& id)
{
    Telegram::InlineKeyboardMarkup::Ptr inlineKeyboardMarkup;
    Telegram::InlineKeyboardButton::Ptr inlineKeyboardButton;
    inlineKeyboardButton                  = Telegram::InlineKeyboardButton::Ptr::create();
    inlineKeyboardButton->m_text          = "New Sentence";
    inlineKeyboardButton->m_callback_data = "New";
    inlineKeyboardMarkup                  = Telegram::InlineKeyboardMarkup::Ptr::create();
    inlineKeyboardMarkup->m_inline_keyboard.resize(1);
    inlineKeyboardMarkup->m_inline_keyboard[0].push_back(inlineKeyboardButton);

    return m_api
        .sendMessage(id,
                     m_sentence.first,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     std::nullopt,
                     inlineKeyboardMarkup)
        .has_value();
}

bool TranslateItBot::replaceSentence(const qint64& chat_id, const qint64& message_id)
{
    Telegram::InlineKeyboardMarkup::Ptr inlineKeyboardMarkup;
    Telegram::InlineKeyboardButton::Ptr inlineKeyboardButton;
    inlineKeyboardButton                  = Telegram::InlineKeyboardButton::Ptr::create();
    inlineKeyboardButton->m_text          = "Skip Sentence";
    inlineKeyboardButton->m_callback_data = "Skip";
    inlineKeyboardMarkup                  = Telegram::InlineKeyboardMarkup::Ptr::create();
    inlineKeyboardMarkup->m_inline_keyboard.resize(1);
    inlineKeyboardMarkup->m_inline_keyboard[0].push_back(inlineKeyboardButton);
    m_sentenceStorage.getRandomSentence(m_sentence);

    return m_api
        .editMessageText(m_sentence.second,
                         chat_id,
                         message_id,
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         std::nullopt,
                         inlineKeyboardMarkup)
        .has_value();
}

bool TranslateItBot::proceedUpdateWithMessage(const Telegram::Message::Ptr& message)
{
    if (message->m_text == "/start")
    {
        return sendNewSentence(message->m_from->m_id);
    }
    else
    {
        return sendTranslation(message->m_from->m_id);
    }
}
