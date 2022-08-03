#include <QFileInfo>

#include "sentencetorage.h"

SentenceStorage::SentenceStorage(const QString& filePath) : m_state(State::Uninitialized)
{
    m_state = load(filePath) ? State::Initialized : State::Error;
}

bool SentenceStorage::load(const QString& filePath)
{
    QStringList langiagesList = QFileInfo(filePath).fileName().split(QRegExp("[-.]"));
    if (langiagesList.size() != 3 && (Languages.find(langiagesList[0]) != Languages.cend()) &&
        (Languages.find(langiagesList[1]) != Languages.cend()))
        return false;
    m_languages.first  = Languages[langiagesList[0]];
    m_languages.second = Languages[langiagesList[1]];

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        while (not file.atEnd())
        {
            QList<QByteArray> query = file.readLine().split(0x09);
            if (query.size() == 4)
            {
                m_sentences.push_back(Sentence(query[1], query[3]));
            }
        }
        file.close();
        return true;
    }
    file.close();
    return false;
}

// TODO: ref?
const QPair<Language, Language>& SentenceStorage::languages() const
{
    return m_languages;
}

Sentence SentenceStorage::randomSentence() const
{
    if (not m_sentences.size()) Sentence();

    quint32 id = QRandomGenerator::global()->bounded(m_sentences.size());

    return m_sentences[id];
}

bool SentenceStorage::isOpen() const
{
    return m_state == State::Initialized;
}

State SentenceStorage::state() const
{
    return m_state;
}
