#include "userstoragedb.h"

#include <QDebug>
#include <QFile>
#include <QSqlQuery>
#include <QSqlRecord>

UserStorageDB::UserStorageDB(const QString& path)
{
    QString dbPath = path + "/" + "TranslateItBotDB.sqlite";
    if (!QFile(dbPath).exists())
    {
        qInfo() << "Database doesn't exist. Creating it.";
        if (not createDataBase(dbPath))
            m_state = State::Uninitialized;
        else
            qInfo() << "Database created successfully";
    }
    else
    {
        qInfo() << "Connecting to an existing database";
        if (not openDataBase(dbPath))
            m_state = State::Uninitialized;
        else
            qInfo() << "Database opened successfully";
    }

    m_state = State::Initialized;
}

UserStorageDB::~UserStorageDB()
{
    if (m_state == State::Initialized) m_db.close();
}

bool UserStorageDB::createDataBase(const QString& path)
{
    if (not openDataBase(path))
    {
        qCritical() << "Can not open database!";
        return false;
    }

    if (not createTables())
    {
        qCritical() << "Can not create database tables!";
        return false;
    }

    return true;
}

bool UserStorageDB::createTables()
{
    QSqlQuery query(m_db);

    return query.exec("CREATE TABLE `User` ( \
                           `id`	INTEGER NOT NULL UNIQUE, \
                           `MinDifficulty`	INTEGER DEFAULT 0, \
                           `MaxDifficulty`	INTEGER DEFAULT 4, \
                           `LangShow`       TEXT    DEFAULT \"Undefined\", \
                           `LangHide`       TEXT    DEFAULT \"Undefined\", \
                           `LastSentence`	INTEGER DEFAULT 0, \
                           PRIMARY KEY(`id`) \
                      );");
}

bool UserStorageDB::openDataBase(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    return m_db.open();
}

State UserStorageDB::state() const
{
    return m_state;
}

QVariant UserStorageDB::queryValue(const QSqlQuery& query, const QString& name) const
{
    const int index = query.record().indexOf(name);
    if (index != -1) return query.value(index);
    return QVariant(0);
}

User::SPtr UserStorageDB::findOrCreate(qint64 id) const
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM user WHERE id = :id");
    query.bindValue(":id", id);

    User::SPtr user = User::SPtr(new User(id));
    if (query.exec())
    {
        if (query.next())
        {
            user->setDifficultyMin(queryValue(query, "MinDifficulty").toInt());
            user->setDifficultyMax(queryValue(query, "MaxDifficulty").toInt());
            user->setLangShow(queryValue(query, "LangShow").toString());
            user->setLangHide(queryValue(query, "LangHide").toString());
            user->setLastSentence(queryValue(query, "LastSentence").toInt());
        }
        else
        {
            addUser(id);
        }
    }

    return user;
}

bool UserStorageDB::addUser(qint64 id) const
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO User (id) VALUES (:id)");
    query.bindValue(":id", id);
    return query.exec();
}

bool UserStorageDB::save(const qint64   id,
                         const quint8   minDifficulty,
                         const quint8   maxDifficulty,
                         const QString& langShow,
                         const QString& langHide,
                         const int      lastSentence) const
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE User SET MinDifficulty = :minDifficulty, MaxDifficulty = :maxDifficulty, LangShow = "
                  ":langShow, LangHide = :langHide, LastSentence = :lastSentence WHERE id = :id");
    query.bindValue(":minDifficulty", minDifficulty);
    query.bindValue(":maxDifficulty", maxDifficulty);
    query.bindValue(":langShow", langShow);
    query.bindValue(":langHide", langHide);
    query.bindValue(":lastSentence", lastSentence);
    query.bindValue(":id", id);
    return query.exec();
}

bool UserStorageDB::save(User::SPtr user) const
{
    return save(user->id(),
                user->difficultyMin(),
                user->difficultyMax(),
                user->langShow(),
                user->langHide(),
                user->lastSentence());
}
