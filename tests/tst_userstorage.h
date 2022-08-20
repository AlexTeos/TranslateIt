#include <QtAlgorithms>
#include <QtTest>

#include "../src/userstorage.h"

class TestUserStorage : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void findOrCreateTestCase();

private:
    QVector<User>               m_users;
    QScopedPointer<UserStorage> m_userStorage;
    const QString               m_workFolder = "./TestUserStorage";
};
