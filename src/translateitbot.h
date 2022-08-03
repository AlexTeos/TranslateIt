#ifndef TRANSLATEITBOT_H
#define TRANSLATEITBOT_H

#include <QString>

#include <telegramapi.h>

#include "languagestorage.h"

class TranslateItBot
{
public:
    TranslateItBot(const QString& token, const QString& tmx);

    void start();
    bool sendNewSentence(const qint64& id);

private:
    State                           m_state;
    LanguageStorage                 m_languageStorage;
    QSharedPointer<SentenceStorage> m_sentenceStorage;
    Telegram::Api                   m_api;
    qint64                          m_offset;
};

#endif // TRANSLATEITBOT_H
