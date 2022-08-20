#ifndef USERSTORAGEDB_H
#define USERSTORAGEDB_H

#include <QSqlDatabase>

#include "common.h"
#include "user.h"

class UserStorageDB
{
public:
    UserStorageDB(const QString& path);
    ~UserStorageDB();

    State               state() const;
    std::optional<User> findOrCreate(qint64 id) const;
    bool                save(const User& user) const;

private:
    bool     createDataBase(const QString& path);
    bool     addUser(qint64 id) const;
    QVariant queryValue(const QSqlQuery& query, const QString& name) const;
    bool     openDataBase(const QString& path);
    bool     createTables();
    bool     save(const qint64   id,
                  const quint8   minDifficulty,
                  const quint8   maxDifficulty,
                  const QString& langShow,
                  const QString& langHide,
                  const int      lastSentence) const;

    QSqlDatabase m_db;
    State        m_state;
};

#endif // USERSTORAGEDB_H
