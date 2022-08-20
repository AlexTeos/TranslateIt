#include <QtAlgorithms>
#include <QtTest>

#include "../src/usercache.h"

class TestUserCache : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void insertTestCase();
    void containsTestCase();
    void userTestCase();

private:
    QVector<User> m_users;
    UserCache     m_cache;
};
