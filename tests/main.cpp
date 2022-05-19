#include "tst_sentencestorage.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    TESTLIB_SELFCOVERAGE_START(TestObject)
    TestSentenceStorage tst_sentenceStorage;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tst_sentenceStorage, argc, argv);
}
