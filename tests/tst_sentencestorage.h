#include <QtAlgorithms>
#include <QtTest>

#include "../src/sentencestorage.h"

class TestSentenceStorage : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void cleanupTestGetRandomSentence();

private:
    SentenceStorage m_sentenceStorage;
};
