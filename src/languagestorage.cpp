#include "languagestorage.h"

#include <QDir>

LanguageStorage::LanguageStorage(const QString& tsvPath) : m_state(State::Uninitialized)
{
    m_state = load(tsvPath) ? State::Initialized : State::Error;
}

QSharedPointer<SentenceStorage> LanguageStorage::sentenceStorage(Language langShow, Language langHide) const
{
    auto pred = [langShow, langHide](auto sentenceStorage) {
        return (sentenceStorage.get()->languages().first == langShow &&
                sentenceStorage.get()->languages().second == langHide);
    };

    auto iter = std::find_if(m_sentenceStorages.begin(), m_sentenceStorages.end(), pred);

    return iter != m_sentenceStorages.end() ? *iter : QSharedPointer<SentenceStorage>();
}

bool LanguageStorage::load(const QString& tsvPath)
{
    QStringList tsvFiles = QDir(tsvPath).entryList(QStringList() << "*.tsv", QDir::Files);
    for (const auto& tsvFile : tsvFiles)
    {
        QSharedPointer<SentenceStorage> sentenceStorage =
            QSharedPointer<SentenceStorage>(new SentenceStorage(tsvPath + tsvFile));
        if (sentenceStorage.get()->state() == State::Initialized) m_sentenceStorages.push_back(sentenceStorage);
    }

    return m_sentenceStorages.size();
}

State LanguageStorage::state() const
{
    return m_state;
}

QVector<QPair<Language, Language>> LanguageStorage::languages() const
{
    QVector<QPair<Language, Language>> languages;
    for (const auto& sentenceStorage : m_sentenceStorages)
    {
        languages.push_back(sentenceStorage.get()->languages());
    }
    return languages;
}

std::function<SentencePtr()> LanguageStorage::sentenceGetter(Language langShow, Language langHide) const
{
    auto sentenceStorageDetermined = sentenceStorage(langShow, langHide);

    if (not sentenceStorageDetermined) return std::function<SentencePtr()>();

    return std::function<SentencePtr()>(
        [sentenceStorageDetermined]() { return sentenceStorageDetermined->randomSentence(); });
}
