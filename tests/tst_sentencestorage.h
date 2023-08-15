#include <QtAlgorithms>
#include <QtTest>

#include "../src/sentencestorage.h"

class TestSentenceStorage : public QObject
{
    Q_OBJECT

public:
    TestSentenceStorage(const QString& tsvPath) : m_tsvPath(tsvPath){};

private slots:
    void initTestCase();
    void cleanupTestCase();
    void getNextSentence();

private:
    QVector<SentenceStorage> m_sentenceStorages;
    QString                  m_tsvPath;
};
