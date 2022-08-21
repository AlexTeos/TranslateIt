#include "tst_usercache.h"

void TestUserCache::initTestCase()
{
    User user(1);
    user.setDifficultyMin(1);
    user.setDifficultyMax(3);
    user.setLangShow("RU");
    user.setLangHide("FI");
    user.setLastSentence(2);
    m_users.push_back(user);

    user.setId(2);
    user.setDifficultyMin(0);
    user.setDifficultyMax(4);
    user.setLangShow("EN");
    user.setLangHide("FI");
    user.setLastSentence(0);
    m_users.push_back(user);

    user.setId(3462);
    user.setDifficultyMin(3);
    user.setDifficultyMax(4);
    user.setLangShow("RU");
    user.setLangHide("EN");
    user.setLastSentence(234);
    m_users.push_back(user);
}

void TestUserCache::cleanupTestCase() {}

void TestUserCache::insertTestCase()
{
    for (int i = 0; i < m_users.count(); ++i)
    {
        auto user = User::SPtr(new User(m_users[i]));
        m_cache.insert(user);
    }
}

void TestUserCache::containsTestCase()
{
    for (int i = 0; i < m_users.count(); ++i)
    {
        QVERIFY(m_cache.contains(m_users[i].id()));
    }
    QVERIFY(m_cache.contains(0) == false);
    QVERIFY(m_cache.contains(3463) == false);
}

void TestUserCache::userTestCase()
{
    for (int i = 0; i < m_users.count(); ++i)
    {
        auto user = m_cache.user(m_users[i].id());
        QVERIFY(user->difficultyMin() == m_users[i].difficultyMin());
        QVERIFY(user->difficultyMax() == m_users[i].difficultyMax());
        QVERIFY(user->langShow() == m_users[i].langShow());
        QVERIFY(user->langHide() == m_users[i].langHide());
        QVERIFY(user->lastSentence() == m_users[i].lastSentence());
    }
}

void TestUserCache::flushTestCase()
{
    QVERIFY(m_cache.flush().size() == m_users.size());
}

void TestUserCache::expiredTestCase()
{
    m_cache.flush();
    int i = 0;
    for (; i < m_cacheSize; ++i)
    {
        auto user = User::SPtr(new User(i));
        QVERIFY(not m_cache.insert(user));
    }

    auto user = User::SPtr(new User(i++));
    QVERIFY(m_cache.insert(user));
    QVERIFY(m_cache.getExpired()->id() == 0);

    QVERIFY(m_cache.insert(User::SPtr(new User(i++))));
    QVERIFY(m_cache.insert(User::SPtr(new User(i++))));
    QVERIFY(m_cache.insert(User::SPtr(new User(i++))));

    QVERIFY(m_cache.getExpired()->id() == 1);
    QVERIFY(m_cache.getExpired()->id() == 2);
    QVERIFY(m_cache.getExpired()->id() == 3);

    QVERIFY(m_cache.user(4));
    QVERIFY(m_cache.user(6));
    QVERIFY(m_cache.user(8));

    QVERIFY(m_cache.insert(User::SPtr(new User(i++))));
    QVERIFY(m_cache.insert(User::SPtr(new User(i++))));
    QVERIFY(m_cache.insert(User::SPtr(new User(i++))));

    QVERIFY(m_cache.getExpired()->id() == 5);
    QVERIFY(m_cache.getExpired()->id() == 7);
    QVERIFY(m_cache.getExpired()->id() == 9);

    QVERIFY(not m_cache.getExpired());
}
