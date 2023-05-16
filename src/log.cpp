#include "log.h"

Log* Log::m_instance = nullptr;

Log::Log()
{
    m_state = State::Uninitialized;
}

Log& Log::instance()
{
    static Log the_instance;
    return the_instance;
}

State Log::configure(QString dir, QString name, qint64 max_size /*, bool debug*/)
{
    m_work_directory = dir;
    m_log_filename   = name;
    m_max_size       = max_size;
    //m_debug          = debug;

    QFile::remove(m_work_directory + m_log_filename);
    m_state = State::Initialized;

    return m_state;
}

QString Log::add(QString type, const char* function, QString msg, const char* file, int line)
{
    QString date_time_string = Log::instance().m_date_time.currentDateTime().toString("<dd-MM-yyyy hh:mm:ss>");
    QString out              = QString("%1 %2: [%3] \"%4\" at file: %5:%6")
                      .arg(date_time_string, type, function, msg, file, QString::number(line));

    if (Log::instance().m_state == State::Initialized /* && !((type == "Debug") && !Log::instance().m_debug)*/)
    {
        QFile log_file(Log::instance().m_work_directory + Log::instance().m_log_filename);

        if (log_file.size() > Log::instance().m_max_size) log_file.remove();

        if (log_file.open(QIODevice::Append))
        {
            QTextStream stream(&log_file);
            stream << out << Qt::endl;
        }
        log_file.close();
    }

    return out;
}
