#ifndef LANGUAGESTORAGE_H
#define LANGUAGESTORAGE_H

#include <QSharedPointer>

#include "sentencestorage.h"

class LanguageStorage
{
public:
    LanguageStorage(const QString& tsvPath);

    QSharedPointer<SentenceStorage>    sentenceStorage(Language langShow, Language langHide) const;
    std::function<SentenceCPtr(int&)>   sentenceGetter(Language langShow,
                                                      Language langHide,
                                                      quint8   difficultyMin,
                                                      quint8   difficultyMax) const;
    bool                               load(const QString& tsvPath);
    State                              state() const;
    QVector<QPair<Language, Language>> languages() const;

private:
    QVector<QSharedPointer<SentenceStorage>> m_sentenceStorages;
    State                                    m_state;
};

#endif // LANGUAGESTORAGE_H
