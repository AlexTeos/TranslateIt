#ifndef TRANSLATEITBOT_H
#define TRANSLATEITBOT_H

#include <QElapsedTimer>
#include <QString>

#include "languagestorage.h"
#include "translateitapi.h"
#include "userstorage.h"

class TranslateItBot : public QObject
{
    Q_OBJECT
public:
    TranslateItBot(const QString& token, const QString& tmx, const QString& localFolder, const QString& adminId);

    void checkUpdates();
    bool processCallBack(Telegram::CallbackQuery::Ptr callback);
    bool processMessage(Telegram::Message::Ptr message);
    bool processCmd(User::SPtr user, Telegram::Message::Ptr message, QString cmd, QString arg = "");
    bool checkAndSetUserSentenceGetter(User::SPtr user);
    bool checkIsUserConfigured(User::SPtr user);
    bool notifyAdmin(QString message);

public slots:
    void telegramError(Telegram::TelegramError error);
    void networkError(Telegram::NetworkError error);

private:
    State           m_state;
    LanguageStorage m_languageStorage;
    TranslateItApi  m_api;
    UserStorage     m_users;
    qint64          m_offset;
    QElapsedTimer   m_backupTimer;
    const qint64    m_backupInterval = 60 * 60 * 1000;
    const QString   m_adminId;
};

#endif // TRANSLATEITBOT_H
