#include <QCoreApplication>
#include <QSettings>

#include "translateitbot.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TranslateIt");
    if (argc > 1) settings.setValue("TelegramBotToken", QString(argv[1]));
    if (argc > 2) settings.setValue("TSVPath", QString(argv[2]));

    TranslateItBot bot(settings.value("TelegramBotToken").toString(), settings.value("TSVPath").toString());
    bot.checkUpdates();

    return 0;
}
