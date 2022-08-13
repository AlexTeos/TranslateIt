#ifndef SENTENCESTORAGE_H
#define SENTENCESTORAGE_H

#include <QFile>
#include <QHash>
#include <QRandomGenerator>
#include <QString>
#include <QXmlStreamReader>

#include "common.h"

enum class Language
{
    Undefined,
    EN,
    RU,
    FI
};

static const QHash<QString, Language> Languages{{QStringLiteral("EN"), Language::EN},
                                                {QStringLiteral("RU"), Language::RU},
                                                {QStringLiteral("FI"), Language::FI}};

struct Sentence
{
    QString first;
    QString second;
    int     difficulty;
};

constexpr quint8 MinDifficulty = 0;
constexpr quint8 MaxDifficulty = 4;

using SentenceStorageContainer = QVector<Sentence>;
using SentenceCPtr             = SentenceStorageContainer::ConstIterator;

class SentenceStorage
{
public:
    SentenceStorage(const QString& filePath);

    //TODO: add consistent reading
    SentenceCPtr                     nextSentence(int& currentSentenceIndex,
                                                  int  difficultyMin = MinDifficulty,
                                                  int  difficultyMax = MaxDifficulty) const;
    bool                             isOpen() const;
    State                            state() const;
    const QPair<Language, Language>& languages() const;

private:
    //TODO: do it in other thread
    bool load(const QString& filePath);

    QPair<Language, Language> m_languages;
    State                     m_state;
    SentenceStorageContainer  m_sentences;
};

#endif // SENTENCESTORAGE_H
