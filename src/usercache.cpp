#include "usercache.h"

bool UserCache::contains(qint64 userId) const
{
    return m_users.contains(userId);
}

UserCache::Iterator UserCache::user(qint64 userId)
{
    return m_users.find(userId);
}

UserCache::ConstIterator UserCache::end() const
{
    return m_users.end();
}

UserCache::Iterator UserCache::insert(const User& user)
{
    return m_users.insert(user.id(), user);
}
