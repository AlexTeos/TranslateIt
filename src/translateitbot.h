#ifndef TRANSLATEITBOT_H
#define TRANSLATEITBOT_H

#include <QString>

#include <telegramapi.h>

#include "sentencestorage.h"

class TranslateItBot
{
public:
    TranslateItBot(const QString& token, const QString& tmx);

    void start();
    bool sendNewSentence(const qint64& id);

private:
    State           m_state;
    SentenceStorage m_sentenceStorage;
    Telegram::Api   m_api;
    Sentence        m_sentence;
    qint64          m_offset;
};

#endif // TRANSLATEITBOT_H
