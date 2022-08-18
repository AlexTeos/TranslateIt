#include "tst_userstoragedb.h"

void TestUserStorageDB::initTestCase()
{
    QFile(m_dbPath).remove();
    m_db.reset(new UserStorageDB(m_dbPath));
    QVERIFY(m_db->state() == State::Initialized);
}

void TestUserStorageDB::cleanupTestCase()
{
    m_db.reset();
    QFile(m_dbPath).remove();
}

void TestUserStorageDB::userTestCase()
{
    m_db->findOrCreate(1);
    m_db->findOrCreate(2);
    m_db->findOrCreate(3462);

    User user;
    user.setId(1);
    user.setDifficultyMin(1);
    user.setDifficultyMax(3);
    user.setLangShow("RU");
    user.setLangHide("FI");
    user.setLastSentence(2);
    QVERIFY(m_db->save(user));

    user.setId(2);
    user.setDifficultyMin(0);
    user.setDifficultyMax(4);
    user.setLangShow("EN");
    user.setLangHide("FI");
    user.setLastSentence(0);
    QVERIFY(m_db->save(user));

    user.setId(3462);
    user.setDifficultyMin(3);
    user.setDifficultyMax(4);
    user.setLangShow("RU");
    user.setLangHide("EN");
    user.setLastSentence(234);
    QVERIFY(m_db->save(user));

    {
        std::optional<User> user = m_db->findOrCreate(1);
        QVERIFY(user.has_value());
        QVERIFY(user->difficultyMin() == 1);
        QVERIFY(user->difficultyMax() == 3);
        QVERIFY(user->langShow() == "RU");
        QVERIFY(user->langHide() == "FI");
        QVERIFY(user->lastSentence() == 2);
    }
    {
        std::optional<User> user = m_db->findOrCreate(2);
        QVERIFY(user.has_value());
        QVERIFY(user->difficultyMin() == 0);
        QVERIFY(user->difficultyMax() == 4);
        QVERIFY(user->langShow() == "EN");
        QVERIFY(user->langHide() == "FI");
        QVERIFY(user->lastSentence() == 0);
    }
    {
        std::optional<User> user = m_db->findOrCreate(3462);
        QVERIFY(user.has_value());
        QVERIFY(user->difficultyMin() == 3);
        QVERIFY(user->difficultyMax() == 4);
        QVERIFY(user->langShow() == "RU");
        QVERIFY(user->langHide() == "EN");
        QVERIFY(user->lastSentence() == 234);
    }
}
