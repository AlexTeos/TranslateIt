#ifndef TRANSLATEITBOT_H
#define TRANSLATEITBOT_H

#include <QString>

#include "TelegramAPI/api.h"
#include "sentencestorage.h"

class TranslateItBot
{
public:
    TranslateItBot(const QString& token, const QString& tmx);

    void start();
    bool proceedUpdateWithMessage(const Telegram::Message::Ptr& message);
    bool proceedUpdateWithCallback(const Telegram::CallbackQuery::Ptr& callback);
    bool sendNewSentence(const qint64& id);
    bool sendTranslation(const qint64& id);
    bool replaceSentence(const qint64& chat_id, const qint64& message_id);

private:
    State           m_state;
    SentenceStorage m_sentenceStorage;
    Telegram::Api   m_api;
    Sentence        m_sentence;
    qint64          m_offset;
};

#endif // TRANSLATEITBOT_H
