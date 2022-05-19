#ifndef SENTENCESTORAGE_H
#define SENTENCESTORAGE_H

#include <QFile>
#include <QRandomGenerator>
#include <QString>
#include <QXmlStreamReader>

typedef QPair<QString, QString> Sentence;

class SentenceStorage
{
public:
    SentenceStorage(){};
    SentenceStorage(const QString& fileName);

    //TODO: do it in other thread
    bool setXMLFile(const QString& fileName);
    bool getRandomSentence(Sentence& sentence);

private:
    QXmlStreamReader  m_xmlFile;
    QVector<Sentence> m_sentences;
};

#endif // SENTENCESTORAGE_H
