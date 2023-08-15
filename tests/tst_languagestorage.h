#include <QtAlgorithms>
#include <QtTest>

#include "../src/languagestorage.h"

class TestLanguageStorage : public QObject
{
    Q_OBJECT

public:
    TestLanguageStorage(const QString& tsvPath) : m_languageStorage(tsvPath){};

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testLanguages();
    void testSentenceStorage();

private:
    LanguageStorage m_languageStorage;
};
