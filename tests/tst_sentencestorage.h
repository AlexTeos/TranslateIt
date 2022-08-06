#include <QtAlgorithms>
#include <QtTest>

#include "../src/sentencestorage.h"

class TestSentenceStorage : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void getNextSentence();

private:
    QVector<SentenceStorage> m_sentenceStorages;
};
