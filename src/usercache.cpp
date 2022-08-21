#include "usercache.h"

bool UserCache::contains(qint64 userId) const
{
    return m_users.contains(userId);
}

User::SPtr UserCache::user(qint64 userId)
{
    return m_users.find(userId).value();
}

void UserCache::insert(User::SPtr user)
{
    m_users.insert(user->id(), user);
    m_usersQueue.push_back(user);
    return;
}
