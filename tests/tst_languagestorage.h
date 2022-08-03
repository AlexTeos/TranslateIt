#include <QtAlgorithms>
#include <QtTest>

#include "../src/languagestorage.h"

class TestLanguageStorage : public QObject
{
    Q_OBJECT

public:
    TestLanguageStorage() : m_languageStorage(""){};

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testLanguages();
    void testSentenceStorage();

private:
    LanguageStorage m_languageStorage;
};
