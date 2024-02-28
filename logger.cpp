#include "Logger.h"
#include <QDateTime>

Logger::Logger(const QString& baseFilename) : logFileNumber(1) {
    QString filename = baseFilename + "_" + QString::number(logFileNumber) + ".txt";
    outputFile.open(filename.toStdString(), std::ios::app); // Open file in append mode
}

Logger::~Logger() {
    if (outputFile.is_open()) {
        outputFile.close(); // Close the file
    }
}

void Logger::logMessage(const QString& message) {
    if (outputFile.is_open()) {
        // Get current date and time
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString timestamp = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

        // Log message with timestamp
        outputFile << "[" << timestamp.toStdString() << "] " << message.toStdString() << std::endl;

    }
}
