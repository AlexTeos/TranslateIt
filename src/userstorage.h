#ifndef USERSTORAGE_H
#define USERSTORAGE_H

#include "usercache.h"
#include "userstoragedb.h"

class UserStorage
{
public:
    UserStorage(const QString& path) : m_cache(20), m_db(path){};

    User::SPtr findOrCreate(qint64 id);
    bool       backup();

private:
    UserCache     m_cache;
    UserStorageDB m_db;
};

#endif // USERSTORAGE_H
