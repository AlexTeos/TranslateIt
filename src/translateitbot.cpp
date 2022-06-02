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

    m_sentenceStorage.getRandomSentence(m_sentence);

    return m_api
        .sendMessage(id,
                     m_sentence.second + "\n" + "\n<tg-spoiler>" + m_sentence.first + "</tg-spoiler>",
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
