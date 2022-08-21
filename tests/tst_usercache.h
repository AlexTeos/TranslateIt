#include <QtAlgorithms>
#include <QtTest>

#include "../src/usercache.h"

class TestUserCache : public QObject
{
    Q_OBJECT
public:
    TestUserCache() : m_cache(m_cacheSize){};

private slots:
    void initTestCase();
    void cleanupTestCase();
    void insertTestCase();
    void containsTestCase();
    void userTestCase();
    void flushTestCase();
    void expiredTestCase();

private:
    const int     m_cacheSize = 10;
    QVector<User> m_users;
    UserCache     m_cache;
};
