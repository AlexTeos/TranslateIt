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
    EN,
    RU,
    FI
};

static const QHash<QString, Language> Languages{{QStringLiteral("EN"), Language::EN},
                                                {QStringLiteral("RU"), Language::RU},
                                                {QStringLiteral("FI"), Language::FI}};

typedef QPair<QString, QString> Sentence;

class SentenceStorage
{
public:
    SentenceStorage(const QString& filePath);

    //TODO: add consistent reading
    //TODO: return ref?
    Sentence                         randomSentence() const;
    bool                             isOpen() const;
    State                            state() const;
    const QPair<Language, Language>& languages() const;

private:
    //TODO: do it in other thread
    bool load(const QString& filePath);

    QPair<Language, Language> m_languages;
    State                     m_state;
    QVector<Sentence>         m_sentences;
};

#endif // SENTENCESTORAGE_H
