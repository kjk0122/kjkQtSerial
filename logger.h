#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QTextStream>
#include <QString>

class Logger {
public:
    Logger(const QString& baseFilename);
    ~Logger();
    //메세지 변수
    void logMessage(const QString& message);
    void updateConnection(const QString& newBaseFilename);

private:
    QFile outputFile;
    QTextStream textStream;
    QString currentBaseFilename;
};

#endif
