#include "userstorage.h"

User::SPtr UserStorage::findOrCreate(qint64 id)
{
    if (not m_cache.contains(id)) m_cache.insert(m_db.findOrCreate(id));
    return m_cache.user(id);
}
