#include <QtAlgorithms>
#include <QtTest>

#include "../src/userstoragedb.h"

class TestUserStorageDB : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void userTestCase();

private:
    QScopedPointer<UserStorageDB> m_db;
    const QString                 m_dbPath = "db.sqlite";
};
