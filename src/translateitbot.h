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
    State                        m_state;
    LanguageStorage              m_languageStorage;
    std::function<SentencePtr()> m_newSentence;
    bool                         m_reversedSentenceStorage = false;
    Telegram::Api                m_api;
    qint64                       m_offset;
};

#endif // TRANSLATEITBOT_H
