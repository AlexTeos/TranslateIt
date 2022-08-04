#include "tst_sentencestorage.h"

void TestSentenceStorage::initTestCase()
{
    QStringList tsvFiles = QDir().entryList(QStringList() << "*.tsv", QDir::Files);
    QVERIFY(tsvFiles.size());
    for (const auto& tsvFile : tsvFiles)
    {
        SentenceStorage sentenceStorage(tsvFile);
        QVERIFY(sentenceStorage.state() == State::Initialized);
        m_sentenceStorages.push_back(std::move(sentenceStorage));
    }
}

void TestSentenceStorage::cleanupTestCase() {}

void TestSentenceStorage::getRandomSentence()
{
    for (const auto& sentenceStorage : m_sentenceStorages)
    {
        for (int i = 0; i < 10; ++i)
        {
            QVERIFY(sentenceStorage.randomSentence()->first != "");
        }
    }
}
