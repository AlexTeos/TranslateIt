#include "usercache.h"

bool UserCache::contains(qint64 userId) const
{
    return m_ids.contains(userId);
}

User::SPtr UserCache::user(qint64 userId)
{
    m_users.splice(m_users.end(), m_users, m_ids.find(userId).value());
    return *m_ids.find(userId).value();
}

bool UserCache::insert(User::SPtr user)
{
    m_users.push_back(user);
    m_ids.insert(user->id(), std::prev(m_users.cend()));
    return m_users.size() > m_size;
}

User::SPtr UserCache::getExpired()
{
    if (m_users.size() > m_size)
    {
        auto user = *m_users.begin();
        m_users.pop_front();
        m_ids.remove(user->id());

        return user;
    }

    return nullptr;
}

UserCache::UserContainer UserCache::flush()
{
    m_ids.clear();
    UserContainer ret = m_users;
    m_users.clear();
    return ret;
}
