#include "tst_userstoragedb.h"

void TestUserStorageDB::initTestCase()
{
    QVERIFY(QDir().mkdir(m_workFolder));
    m_db.reset(new UserStorageDB(m_workFolder));
    QVERIFY(m_db->state() == State::Initialized);

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

void TestUserStorageDB::cleanupTestCase()
{
    m_db.reset();
    QSqlDatabase::removeDatabase(QLatin1String(QSqlDatabase::defaultConnection));
    QVERIFY(QDir(m_workFolder).removeRecursively());
}

void TestUserStorageDB::userTestCase()
{
    for (int i = 0; i < m_users.count(); ++i)
    {
        QVERIFY(m_db->findOrCreate(m_users[i].id()));
        QVERIFY(m_db->save(m_users[i]));

        auto user = m_db->findOrCreate(1);
        QVERIFY(user);
        QVERIFY(user->difficultyMin() == 1);
        QVERIFY(user->difficultyMax() == 3);
        QVERIFY(user->langShow() == "RU");
        QVERIFY(user->langHide() == "FI");
        QVERIFY(user->lastSentence() == 2);
    }
}
