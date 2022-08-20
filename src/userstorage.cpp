#include "userstorage.h"

UserStorage::Iterator UserStorage::findOrCreate(qint64 id)
{
    if (m_cache.contains(id))
    {
        return m_cache.user(id);
    }
    else
    {
        auto user = m_db.findOrCreate(id);
        // TODO: check user
        return m_cache.insert(*user);
    }
}
