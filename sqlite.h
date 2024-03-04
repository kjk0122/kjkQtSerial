#ifndef SQLITE_H
#define SQLITE_H

#include <QObject>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

class Sqlite : public QObject
{
    Q_OBJECT

public:
    Sqlite(QObject* parent = nullptr);
    ~Sqlite();

    bool openDatabase();
    void closeDatabase();
    void logMessage(const QString& message, qint64 distance, const QString& alarm);

private:
    QSqlDatabase m_database;
};

#endif
