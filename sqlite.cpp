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
    m_database.setDatabaseName("C:/Users/user/Documents/kjkQtSerial/kjktest.db");  // SQLite database file name

    if (!m_database.open()) {
        qDebug() << "Failed to open database:" << m_database.lastError().text();
        return false;
    }

    // Assuming you have a "logs" table in your database with columns "timestamp" and "message"
    QSqlQuery query(m_database);
    query.exec("CREATE TABLE IF NOT EXISTS logs (timestamp DATETIME, message TEXT)");

    return true;
}

void Sqlite::closeDatabase()
{
    if (m_database.isOpen()) {
        m_database.close();
        QSqlDatabase::removeDatabase(m_database.connectionName());
    }
}

void Sqlite::logMessage(const QString& message)
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
    query.prepare("INSERT INTO logs (timestamp, message) VALUES (:timestamp, :message)");
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":message", message);

    if (query.exec()) {
        // Log successfully inserted into the database
    } else {
        qDebug() << "Failed to log message. Error:" << query.lastError().text();
    }
}
