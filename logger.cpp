#include "Logger.h"
#include <QDateTime>
#include <QDebug>

Logger::Logger(const QString& baseFilename) : currentBaseFilename(baseFilename) {

    QString filename = currentBaseFilename + ".txt";
    outputFile.setFileName(filename);

    if (outputFile.open(QIODevice::Append | QIODevice::Text)) {
        textStream.setDevice(&outputFile);
    } else {
        qDebug() << "Failed to open log file" << filename;
    }
}

Logger::~Logger() {
    outputFile.close();
}

void Logger::logMessage(const QString& message) {
    if (outputFile.isOpen()) {
        //시간기록
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString timestamp = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
        textStream << "[" << timestamp << "] " << message << Qt::endl;
        textStream.flush();
    }
}

void Logger::updateConnection(const QString& newBaseFilename) {
    if (newBaseFilename != currentBaseFilename) {
        currentBaseFilename = newBaseFilename;

        outputFile.close();
        QString filename = currentBaseFilename + ".txt";
        outputFile.setFileName(filename);

        if (!outputFile.open(QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Failed to open log file" << filename;
        }

        textStream.setDevice(&outputFile);
    }
}

