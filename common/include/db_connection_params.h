#ifndef DB_CONNECTION_PARAMS_H
#define DB_CONNECTION_PARAMS_H

#include <QString>

namespace db
{

/// <summary>
/// Параметры подключения к БД
/// </summary>
struct DbConnectionParams {
    QString hostname;
    QString driver;
    quint16 port = 5432; // PostgreSQL default
    QString databasename;
    QString username;
    QString password;
};

}

#endif // DB_CONNECTION_PARAMS_H
