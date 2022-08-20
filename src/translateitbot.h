#ifndef TRANSLATEITBOT_H
#define TRANSLATEITBOT_H

#include <QString>

#include <telegramapi.h>

#include "languagestorage.h"
#include "usercache.h"

class TranslateItBot
{
public:
    TranslateItBot(const QString& token, const QString& tmx);

    void start();
    bool sendNewSentence(const qint64& id);
    bool addNewUser(qint64 iserId);

private:
    State           m_state;
    LanguageStorage m_languageStorage;
    Telegram::Api   m_api;
    UserCache       m_users;
    qint64          m_offset;
};

#endif // TRANSLATEITBOT_H
