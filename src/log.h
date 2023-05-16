#ifndef LOG_H
#define LOG_H

#include <QDateTime>
#include <QFile>
#include <QObject>
#include <QTextStream>

#include "common.h"

class Log
{
public:
    explicit Log();
    static Log&    instance();
    State          configure(QString dir, QString name, qint64 max_size /*, bool debug = false*/);
    static QString add(QString type, const char* function, QString msg, const char* file, int line);

private:
    static Log* m_instance;

    //bool      m_debug;
    State     m_state;
    qint64    m_max_size;
    QString   m_work_directory;
    QString   m_log_filename;
    QDateTime m_date_time;
};

#endif // LOG_H
