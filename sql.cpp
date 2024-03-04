#include "sql.h"

DbManager::DbManager(const QString& path) //생성자
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "연결 실패: " << m_db.lastError().text();
        QSqlDatabase::removeDatabase(m_db.connectionName());
        throw std::runtime_error("데이터베이스 연결 실패");
    }
    else
    {
        qDebug() << "연결 성공";
    }
}

DbManager::~DbManager() //소멸자
{
    m_db.close();
    QSqlDatabase::removeDatabase(m_db.connectionName());
}
