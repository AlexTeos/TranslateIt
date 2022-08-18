#ifndef BOTUSER_H
#define BOTUSER_H

#include "sentencestorage.h"

class User
{
public:
    User();

    void setSentenceGetter(const std::function<SentenceCPtr(int&)>& newNewSentence);

    SentenceCPtr newSentence();

    QString langShow() const;
    void    setLangShow(QString newLangShow);

    QString langHide() const;
    void    setLangHide(QString newLangHide);

    quint8 difficultyMin() const;
    void   setDifficultyMin(quint8 newDifficultyMin);

    quint8 difficultyMax() const;
    void   setDifficultyMax(quint8 newDifficultyMax);

    bool reversedSentence() const;
    void setReversedSentence(bool newReversedSentenceStorage);

    qint64 id() const;
    void   setId(qint64 newId);

    int  lastSentence() const;
    void setLastSentence(int newLastSentence);

private:
    qint64                            m_id;
    std::function<SentenceCPtr(int&)> m_newSentence;
    int                               m_lastSentence            = 0;
    bool                              m_reversedSentenceStorage = false;
    QString                           m_langShow                = "Undefined";
    QString                           m_langHide                = "Undefined";
    quint8                            m_difficultyMin           = MinDifficulty;
    quint8                            m_difficultyMax           = MaxDifficulty;
};

#endif // BOTUSER_H
