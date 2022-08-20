#ifndef USERCACHE_H
#define USERCACHE_H

#include <QMap>

#include "user.h"

class UserCache
{
public:
    using UserContaner  = QMap<qint64, User>;
    using Iterator      = UserContaner::Iterator;
    using ConstIterator = UserContaner::ConstIterator;

    bool          contains(qint64 userId) const;
    Iterator      user(qint64 userId);
    ConstIterator end() const;
    Iterator      insert(const User& user);

private:
    UserContaner m_users;
};

#endif // USERCACHE_H
