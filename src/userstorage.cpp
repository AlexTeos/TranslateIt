#include "userstorage.h"

User::SPtr UserStorage::findOrCreate(qint64 id)
{
    if (not m_cache.contains(id))
    {
        if (m_cache.insert(m_db.findOrCreate(id)))
        {
            auto expiredUser = m_cache.getExpired();
            m_db.save(expiredUser);
        }
    }
    return m_cache.user(id);
}
