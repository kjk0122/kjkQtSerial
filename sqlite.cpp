#include "sqlite.h"

Sqlite::Sqlite(QObject* parent)
    : QObject(parent)
{
    if (!openDatabase()) {
        // Handle database opening failure if needed
    }
}

Sqlite::~Sqlite()
{
    closeDatabase();
}

bool Sqlite::openDatabase()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("C:/Users/user/Documents/kjkQtSerial/kjkultra.db");  // db 지정해줘야함

    if (!m_database.open()) {
        qDebug() << "Failed to open database:" << m_database.lastError().text();
        return false;
    }
    //QSL테이블 생성해주기
    QSqlQuery query(m_database);
    query.exec("CREATE TABLE IF NOT EXISTS LOG (timestamp DATETIME, distance INTEGER, alarm TEXT)");

    return true;
}

void Sqlite::closeDatabase()
{
    if (m_database.isOpen()) {
        m_database.close();
        QSqlDatabase::removeDatabase(m_database.connectionName());
    }
}

void Sqlite::logMessage(const QString& message, qint64 distance, const QString& alarm)
{
    if (!m_database.isOpen()) {
        if (!openDatabase()) {
            // Handle database opening failure if needed
            return;
        }
    }

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString timestamp = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    QSqlQuery query(m_database);
    query.prepare("INSERT INTO LOG (timestamp, distance, alarm) VALUES (:timestamp, :distance, :alarm)");
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":distance", distance);
    query.bindValue(":alarm", alarm);

    if (query.exec()) {
        // Log successfully inserted into the database
    } else {
        qDebug() << "Failed to log message. Error:" << query.lastError().text();
    }
}
