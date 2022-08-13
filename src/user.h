#ifndef BOTUSER_H
#define BOTUSER_H

#include "sentencestorage.h"

class User
{
public:
    User();

    void setSentenceGetter(const std::function<SentenceCPtr(int&)>& newNewSentence);

    SentenceCPtr newSentence();

    Language langShow() const;
    void     setLangShow(Language newLangShow);

    Language langHide() const;
    void     setLangHide(Language newLangHide);

    quint8 difficultyMin() const;
    void   setDifficultyMin(quint8 newDifficultyMin);

    quint8 difficultyMax() const;
    void   setDifficultyMax(quint8 newDifficultyMax);

    bool reversedSentence() const;
    void setReversedSentence(bool newReversedSentenceStorage);

private:
    std::function<SentenceCPtr(int&)> m_newSentence;
    int                               m_lastSentence            = 0;
    bool                              m_reversedSentenceStorage = false;
    Language                          m_langShow                = Language::Undefined;
    Language                          m_langHide                = Language::Undefined;
    quint8                            m_difficultyMin           = MinDifficulty;
    quint8                            m_difficultyMax           = MaxDifficulty;
};

#endif // BOTUSER_H
