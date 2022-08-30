#include <QCoreApplication>
#include <QSettings>

#include "translateitbot.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TranslateIt");
    if (argc > 1) settings.setValue("TelegramBotToken", argv[1]);
    if (argc > 2) settings.setValue("TSVPath", argv[2]);

    TranslateItBot bot(settings.value("TelegramBotToken").toString(), settings.value("tsvPath").toString());
    bot.checkUpdates();

    return 0;
}
