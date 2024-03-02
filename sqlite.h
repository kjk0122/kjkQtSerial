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
    explicit Sqlite(QObject* parent = nullptr);
    ~Sqlite();

public slots:
    void logMessage(const QString& message);

private:
    QSqlDatabase m_database;

    bool openDatabase();
    void closeDatabase();
};

#endif
