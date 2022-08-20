#include "tst_userstorage.h"

void TestUserStorage::initTestCase()
{
    QVERIFY(QDir().mkdir(m_workFolder));
    m_userStorage.reset(new UserStorage(m_workFolder));

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

void TestUserStorage::cleanupTestCase()
{
    m_userStorage.reset();
    QSqlDatabase::removeDatabase(QLatin1String(QSqlDatabase::defaultConnection));
    QVERIFY(QDir(m_workFolder).removeRecursively());
}

void TestUserStorage::findOrCreateTestCase()
{
    for (int i = 0; i < m_users.count(); ++i)
    {
        m_users[i].id();
        auto userPtr = m_userStorage->findOrCreate(m_users[i].id());
        userPtr->setDifficultyMin(m_users[i].difficultyMin());
        userPtr->setDifficultyMax(m_users[i].difficultyMax());
        userPtr->setLangShow(m_users[i].langShow());
        userPtr->setLangHide(m_users[i].langHide());
        userPtr->setLastSentence(m_users[i].lastSentence());

        userPtr = m_userStorage->findOrCreate(m_users[i].id());
        QVERIFY(userPtr->difficultyMin() == m_users[i].difficultyMin());
        QVERIFY(userPtr->difficultyMax() == m_users[i].difficultyMax());
        QVERIFY(userPtr->langShow() == m_users[i].langShow());
        QVERIFY(userPtr->langHide() == m_users[i].langHide());
        QVERIFY(userPtr->lastSentence() == m_users[i].lastSentence());
    }
}
