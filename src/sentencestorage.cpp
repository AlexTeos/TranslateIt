#include "sentencestorage.h"

#include <QFileInfo>

SentenceStorage::SentenceStorage(const QString& filePath) : m_state(State::Uninitialized)
{
    m_state = load(filePath) ? State::Initialized : State::Error;
}

bool SentenceStorage::load(const QString& filePath)
{
    QStringList langiagesList = QFileInfo(filePath).baseName().split("-");
    if (langiagesList.size() != 2) return false;
    m_languages.first  = langiagesList[0];
    m_languages.second = langiagesList[1];

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        while (not file.atEnd())
        {
            QList<QByteArray> query = file.readLine().split(0x09);
            if (query.size() == 4)
            {
                if (query[1].contains(". ")) continue; // skip too complicated sentences

                QString sentence    = QString(query[1]).remove("\\n");
                sentence    = QString(query[1]).remove("\\r");
                QString translation = QString(query[3]).remove("\\n");
                translation = QString(query[3]).remove("\\r");
                if (m_sentences.size() > 0 and
                    ((sentence == m_sentences.back().first) or translation == m_sentences.back().second))
                    continue; // skip same sentences

                m_sentences.push_back(
                    Sentence{sentence, translation, qMin<int>(sentence.count(" ") / 5, MaxDifficulty)});
            }
        }
        file.close();
        return true;
    }
    file.close();
    return false;
}

// TODO: ref?
const QPair<QString, QString>& SentenceStorage::languages() const
{
    return m_languages;
}

std::optional<SentenceCPtr> SentenceStorage::nextSentence(int& currentSentenceIndex,
                                                          int  difficultyMin,
                                                          int  difficultyMax) const
{
    bool loopStarted = false;
    do
    {
        currentSentenceIndex++;
        if (currentSentenceIndex >= m_sentences.size())
        {
            currentSentenceIndex = 0;
            if (loopStarted) return std::nullopt;
            loopStarted = true;
        }
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
