#include "tst_sentencestorage.h"

void TestSentenceStorage::initTestCase()
{
    QStringList tmsFiles = QDir().entryList(QStringList() << "*.tmx", QDir::Files);
    QVERIFY(tmsFiles.size());
    QVERIFY(m_sentenceStorage.setXMLFile(tmsFiles[0]));
}

void TestSentenceStorage::cleanupTestCase() {}

void TestSentenceStorage::cleanupTestGetRandomSentence()
{
    Sentence sentence;
    for (int i = 0; i < 10; ++i)
    {
        QVERIFY(m_sentenceStorage.getRandomSentence(sentence));
    }
}
