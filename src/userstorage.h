#ifndef USERSTORAGE_H
#define USERSTORAGE_H

#include "usercache.h"
#include "userstoragedb.h"

class UserStorage
{
public:
    using Iterator      = UserCache::Iterator;
    using ConstIterator = UserCache::ConstIterator;

    UserStorage(const QString& path) : m_db(path){};

    Iterator findOrCreate(qint64 id);

private:
    UserCache     m_cache;
    UserStorageDB m_db;
};

#endif // USERSTORAGE_H
