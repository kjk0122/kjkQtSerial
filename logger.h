#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <QString>

class Logger {
public:
    Logger(const QString& filename);
    ~Logger();

    void logMessage(const QString& message);

private:
    std::ofstream outputFile;
    int logFileNumber;
};

#endif // LOGGER_H
