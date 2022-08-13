#include "user.h"

User::User() {}

void User::setSentenceGetter(const std::function<SentenceCPtr(int&)>& newNewSentence)
{
    m_newSentence = newNewSentence;
}

SentenceCPtr User::newSentence()
{
    m_newSentence(m_lastSentence);
    return m_newSentence(m_lastSentence);
}

Language User::langShow() const
{
    return m_langShow;
}

void User::setLangShow(Language newLangShow)
{
    m_langShow = newLangShow;
}

Language User::langHide() const
{
    return m_langHide;
}

void User::setLangHide(Language newLangHide)
{
    m_langHide = newLangHide;
}

quint8 User::difficultyMin() const
{
    return m_difficultyMin;
}

void User::setDifficultyMin(quint8 newDifficultyMin)
{
    m_difficultyMin = newDifficultyMin;
}

quint8 User::difficultyMax() const
{
    return m_difficultyMax;
}

void User::setDifficultyMax(quint8 newDifficultyMax)
{
    m_difficultyMax = newDifficultyMax;
}

bool User::reversedSentence() const
{
    return m_reversedSentenceStorage;
}

void User::setReversedSentence(bool newReversedSentenceStorage)
{
    m_reversedSentenceStorage = newReversedSentenceStorage;
}
