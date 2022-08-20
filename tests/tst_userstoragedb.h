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
    QVector<User>                 m_users;
    QScopedPointer<UserStorageDB> m_db;
    const QString                 m_workFolder = "./TestUserStorageDB";
};
