#include "sentencestorage.h"

#include <QFileInfo>

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
            if (query[1].contains(". ")) continue; // skip too complicated sentences
            // TODO: filter same sentences
            if (query.size() == 4)
            {
                m_sentences.push_back(Sentence{query[1], query[3], qMin<int>(query[1].count(" ") / 5, MaxDifficulty)});
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

SentencePtr SentenceStorage::nextSentence(int& currentSentenceIndex, int difficultyMin, int difficultyMax) const
{
    // TODO: check looping
    do
    {
        currentSentenceIndex++;
        if (currentSentenceIndex >= m_sentences.size()) currentSentenceIndex = 0;
    } while (m_sentences.at(currentSentenceIndex).difficulty < difficultyMin ||
             m_sentences.at(currentSentenceIndex).difficulty > difficultyMax);

    return m_sentences.cbegin() + currentSentenceIndex;
}

bool SentenceStorage::isOpen() const
{
    return m_state == State::Initialized;
}

State SentenceStorage::state() const
{
    return m_state;
}
