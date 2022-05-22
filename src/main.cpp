#include <QCoreApplication>
#include <QSettings>

#include "translateitbot.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TranslateIt");
    if (argc > 1) settings.setValue("Token", argv[1]);
    if (argc > 2) settings.setValue("SentenceStorage", argv[2]);

    TranslateItBot bot(settings.value("Token").toString(), settings.value("SentenceStorage").toString());
    bot.start();

    return 0;
}
