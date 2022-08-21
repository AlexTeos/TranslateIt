#ifndef TRANSLATEITBOT_H
#define TRANSLATEITBOT_H

#include <QString>

#include <telegramapi.h>

#include "languagestorage.h"
#include "userstorage.h"

class TranslateItBot
{
public:
    TranslateItBot(const QString& token, const QString& tmx);

    void start();
    bool sendNewSentence(const qint64& id);

private:
    State           m_state;
    LanguageStorage m_languageStorage;
    Telegram::Api   m_api;
    UserStorage     m_users;
    qint64          m_offset;
};

#endif // TRANSLATEITBOT_H
