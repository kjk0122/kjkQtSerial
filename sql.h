#ifndef SQL_H
#define SQL_H

#include <QSql>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlDatabase>

class DbManager
{
public:
    DbManager(const QString& path);
private:
    QSqlDatabase m_db;
};
DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "연결 실패";
    }
    else
    {
        qDebug() << "연결 성공";
    }
}
#endif
