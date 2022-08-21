#ifndef USERCACHE_H
#define USERCACHE_H

#include <QMap>
#include <QPair>
#include <QSharedPointer>
#include <list>

#include "user.h"

class UserCache
{
public:
    using UserContainer = std::list<User::SPtr>;
    using IdContainer   = QMap<qint64, UserContainer::const_iterator>;

    UserCache(UserContainer::size_type size) : m_size(size) {}

    bool          contains(qint64 userId) const;
    User::SPtr    user(qint64 userId);
    bool          insert(User::SPtr user);
    User::SPtr    getExpired();
    UserContainer flush();

private:
    IdContainer                    m_ids;
    UserContainer                  m_users;
    const UserContainer::size_type m_size;
};

#endif // USERCACHE_H
