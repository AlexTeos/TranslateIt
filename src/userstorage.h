#ifndef USERSTORAGE_H
#define USERSTORAGE_H

#include <QMap>

#include "user.h"

class UserStorage
{
public:
    using UserContaner  = QMap<qint64, User>;
    using Iterator      = UserContaner::Iterator;
    using ConstIterator = UserContaner::ConstIterator;

    UserStorage();
    bool          contains(qint64 userId) const;
    Iterator      user(qint64 userId);
    ConstIterator end() const;
    Iterator      insert(const User& user);

private:
    UserContaner m_users;
};

#endif // USERSTORAGE_H
