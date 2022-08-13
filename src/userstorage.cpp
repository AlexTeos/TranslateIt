#include "userstorage.h"

UserStorage::UserStorage() {}

bool UserStorage::contains(qint64 userId) const
{
    return m_users.contains(userId);
}

UserStorage::Iterator UserStorage::user(qint64 userId)
{
    return m_users.find(userId);
}

UserStorage::ConstIterator UserStorage::end() const
{
    return m_users.end();
}

UserStorage::Iterator UserStorage::insert(const User& user)
{
    return m_users.insert(user.id(), user);
}
