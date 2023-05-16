#include <QCoreApplication>
#include <QSettings>

#include "log.h"
#include "translateitbot.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    switch (type)
    {
        //case QtDebugMsg:
        //    fprintf(stderr,
        //            "%s\n",
        //            Log::add("Debug", context.function, msg, context.file, context.line).toLocal8Bit().data());
        //    break;
        case QtInfoMsg:
            fprintf(stderr,
                    "%s\n",
                    Log::add("Info", context.function, msg, context.file, context.line).toLocal8Bit().data());
            break;
        case QtWarningMsg:
            fprintf(stderr,
                    "%s\n",
                    Log::add("Warning", context.function, msg, context.file, context.line).toLocal8Bit().data());
            break;
        case QtCriticalMsg:
            fprintf(stderr,
                    "%s\n",
                    Log::add("Critical", context.function, msg, context.file, context.line).toLocal8Bit().data());
            break;
        case QtFatalMsg:
            fprintf(stderr,
                    "%s\n",
                    Log::add("Fatal", context.function, msg, context.file, context.line).toLocal8Bit().data());
            abort();
        default:
            break;
    }
    fflush(stderr);
}

int main(int argc, char* argv[])
{
    qInstallMessageHandler(myMessageOutput);

    Log::instance().configure("./", "log.log", 1024 * 1024 * 128);

    QCoreApplication a(argc, argv);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TranslateIt");
    if (argc > 1) settings.setValue("TelegramBotToken", QString(argv[1]));
    if (argc > 2) settings.setValue("TSVPath", QString(argv[2]));

    qInfo() << "Start bot id:" << settings.value("TelegramBotToken").toString()
            << "TSVPath:" << settings.value("TSVPath").toString();
    TranslateItBot bot(settings.value("TelegramBotToken").toString(), settings.value("TSVPath").toString());
    bot.checkUpdates();

    return 0;
}
