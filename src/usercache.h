#ifndef USERCACHE_H
#define USERCACHE_H

#include <QMap>
#include <QQueue>
#include <QSharedPointer>

#include "user.h"

class UserCache
{
public:
    using UserContaner = QMap<qint64, User::SPtr>;

    bool       contains(qint64 userId) const;
    User::SPtr user(qint64 userId);
    void       insert(User::SPtr user);

private:
    UserContaner       m_users;
    QQueue<User::SPtr> m_usersQueue;
};

#endif // USERCACHE_H
