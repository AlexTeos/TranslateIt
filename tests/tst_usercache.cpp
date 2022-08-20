#include "tst_usercache.h"

void TestUserCache::initTestCase()
{
    User user;
    user.setId(1);
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
        QVERIFY(m_cache.insert(m_users[i]) != m_cache.end());
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
        QVERIFY(user != m_cache.end());
        QVERIFY(user->difficultyMin() == m_users[i].difficultyMin());
        QVERIFY(user->difficultyMax() == m_users[i].difficultyMax());
        QVERIFY(user->langShow() == m_users[i].langShow());
        QVERIFY(user->langHide() == m_users[i].langHide());
        QVERIFY(user->lastSentence() == m_users[i].lastSentence());
    }
}
