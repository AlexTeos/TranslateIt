#ifndef TRANSLATEITAPI_H
#define TRANSLATEITAPI_H

#include <QStringList>

#include <telegramapi.h>

#include "user.h"

class TranslateItApi : public Telegram::Api
{
public:
    bool sendAvailableLanguages(const User::SPtr user, QSet<QString> languages);
    bool editAvailableLanguages(Telegram::Message::Ptr message, QSet<QString> languages);
    bool editDifficulty(Telegram::Message::Ptr message, bool max = false, int minDifficulty = MinDifficulty);
    bool confirmSettings(Telegram::Message::Ptr message);
    bool configureMenuCommands(QVector<QPair<QString, QString>> commands);
    bool sendNewSentence(User::SPtr user);
};

#endif // TRANSLATEITAPI_H
