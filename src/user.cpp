#include "user.h"

void User::setSentenceGetter(const std::function<SentenceCPtr(int&)>& newNewSentence)
{
    m_newSentence = newNewSentence;
}

SentenceCPtr User::newSentence()
{
    return m_newSentence(m_lastSentence);
}

bool User::isSentenceGetterSet()
{
    return bool(m_newSentence);
}

QString User::langShow() const
{
    return m_langShow;
}

void User::setLangShow(QString newLangShow)
{
    m_langShow = newLangShow;
}

QString User::langHide() const
{
    return m_langHide;
}

void User::setLangHide(QString newLangHide)
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

qint64 User::id() const
{
    return m_id;
}

void User::setId(qint64 newId)
{
    m_id = newId;
}

int User::lastSentence() const
{
    return m_lastSentence;
}

void User::setLastSentence(int newLastSentence)
{
    m_lastSentence = newLastSentence;
}
