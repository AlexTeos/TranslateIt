#ifndef SENTENCESTORAGE_H
#define SENTENCESTORAGE_H

#include <QFile>
#include <QRandomGenerator>
#include <QString>
#include <QXmlStreamReader>

typedef QPair<QString, QString> Sentence;

enum SentenceStorageState
{
    Uninitialized = 0,
    Initialized,
    Error
};

class SentenceStorage
{
public:
    SentenceStorage() : m_state(SentenceStorageState::Uninitialized){};
    SentenceStorage(const QString& fileName);

    //TODO: do it in other thread
    bool setXMLFile(const QString& fileName);
    bool getRandomSentence(Sentence& sentence);
    bool isOpen();

private:
    SentenceStorageState m_state;
    QXmlStreamReader     m_xmlFile;
    QVector<Sentence>    m_sentences;
};

#endif // SENTENCESTORAGE_H
