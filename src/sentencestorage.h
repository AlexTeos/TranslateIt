#ifndef SENTENCESTORAGE_H
#define SENTENCESTORAGE_H

#include <QFile>
#include <QRandomGenerator>
#include <QString>
#include <QXmlStreamReader>

#include "common.h"

typedef QPair<QString, QString> Sentence;

class SentenceStorage
{
public:
    SentenceStorage() : m_state(State::Uninitialized){};
    SentenceStorage(const QString& fileName);

    //TODO: do it in other thread
    bool setXMLFile(const QString& fileName);
    //TODO: add consistence reading
    bool getRandomSentence(Sentence& sentence);
    bool isOpen();

private:
    State             m_state;
    QXmlStreamReader  m_xmlFile;
    QVector<Sentence> m_sentences;
};

#endif // SENTENCESTORAGE_H
