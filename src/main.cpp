#include <QCoreApplication>
#include <QSettings>
#include <QThread>

#include "TelegramAPI/api.h"
#include "sentencestorage.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TranslateIt");
    if (argc > 1) settings.setValue("Token", argv[1]);
    if (argc > 2) settings.setValue("SentenceStorage", argv[2]);

    SentenceStorage sentenceStorage(settings.value("SentenceStorage").toString());
    Telegram::Api   api;
    if (api.start(settings.value("Token").toString()))
    {
        qint64   offset;
        Sentence sentence;
        bool     sendTranslation = false;
        while (true)
        {
            std::optional<QVector<Telegram::Update::Ptr>> updates = api.getUpdates(offset);

            if (updates->size())
            {
                for (Telegram::Update::Ptr update : updates.value())
                {
                    offset = update->m_update_id + 1;
                    if (sendTranslation)
                    {
                        api.sendMessage(update->m_message->m_from->m_id, sentence.first);
                        sendTranslation = false;
                    }
                    else
                    {
                        sentenceStorage.getRandomSentence(sentence);
                        api.sendMessage(update->m_message->m_from->m_id, sentence.second);
                        sendTranslation = true;
                    }
                }
            }
            else
            {
                QThread::sleep(1);
            }
        }
    }

    return 0;
}
