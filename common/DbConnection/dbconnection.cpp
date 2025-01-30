#include "dbconnection.h"

using namespace db;

DbConnection::DbConnection(const QString &alias,
                           const QString &hostname,
                           const QString &driver,
                           const quint16 &port,
                           const QString &databasename,
                           const QString &username,
                           const QString &password) noexcept
    : _alias(alias),
      _hostname(hostname),
      _driver(driver),
      _port(port),
      _databasename(databasename),
      _username(username),
      _password(password)
{

}

DbConnection::~DbConnection()
{
    close();
}

bool DbConnection::open() const
{
    QSqlDatabase db = QSqlDatabase::addDatabase(_driver, _alias);
    db.setHostName(_hostname);
    db.setPort(_port);
    db.setDatabaseName(_databasename);
    db.setUserName(_username);
    db.setPassword(_password);

    return db.open();
}

void DbConnection::close() const
{
    QSqlDatabase db = QSqlDatabase::database(_alias);
    db.close();
}

void DbConnection::close(const QString &alias)
{
    QSqlDatabase db = QSqlDatabase::database(alias);
    db.close();
}

bool DbConnection::isOpen(const QString &alias)
{
    QSqlDatabase db = QSqlDatabase::database(alias);
    return db.isOpen();
}

bool DbConnection::reConnect(const quint16 &count) const
{
    for (int i = 0; i < count; i++)
    {
        this->close();
        QSqlDatabase::removeDatabase(_alias);
        QSqlDatabase db = QSqlDatabase::addDatabase(_driver, _alias);
        db.setHostName(_hostname);
        db.setPort(_port);
        db.setDatabaseName(_databasename);
        db.setUserName(_username);
        db.setPassword(_password);
        if (db.open()) {
            return true;
        }
    }

    return false;
}

QString DbConnection::error() const
{
    QSqlDatabase db = QSqlDatabase::database(_alias);
    return db.lastError().text();
}
