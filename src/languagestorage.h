#ifndef LANGUAGESTORAGE_H
#define LANGUAGESTORAGE_H

#include <QSharedPointer>

#include "sentencestorage.h"

class LanguageStorage
{
public:
    LanguageStorage(const QString& tsvPath);

    QSharedPointer<SentenceStorage>   sentenceStorage(QString langShow, QString langHide) const;
    std::function<SentenceCPtr(int&)> sentenceGetter(QString langShow,
                                                     QString langHide,
                                                     quint8  difficultyMin,
                                                     quint8  difficultyMax) const;
    bool                              load(const QString& tsvPath);
    State                             state() const;
    QVector<QPair<QString, QString>>  languages() const;

private:
    QVector<QSharedPointer<SentenceStorage>> m_sentenceStorages;
    State                                    m_state;
};

#endif // LANGUAGESTORAGE_H
