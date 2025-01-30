#ifndef MODEL_BASE_H
#define MODEL_BASE_H

#include <QString>
#include <QDebug>
#include <QStringList>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include "DbConnection/dbconnection.h"
#include "include/db_connection_params.h"

namespace db {

/// <summary>
/// Базовая модель данных для БД
/// </summary>
class DbModelBase
{
protected:
    const QString _alias;
    mutable QString _error;
    const DbConnectionParams _params;

public:
    DbModelBase(const QString &alias, const DbConnectionParams &params) noexcept;
    virtual ~DbModelBase();

    /// <summary>
    /// Соединение с БД
    /// </summary>
    bool setConnection() noexcept;

    /// <summary>
    /// Закрытие cоединение с БД
    /// </summary>
    void closeConnection();

    /// <summary>
    /// Проверка соединения с БД
    /// </summary>
    /// <returns>Результат</returns>
    bool isOpen() const;

    /// <summary>
    /// Возвращает текст ошибки при выполнении запросов к БД
    /// </summary>
    /// <returns>Текст ошибки</returns>
    virtual QString errorText() const { return _error; }

    /// <summary>
    /// Устанавливает текст ошибки при выполнении запросов к БД
    /// </summary>
    /// <param name="txt">Текст ошибки</param>
    virtual void setErrorText(const QString &txt) { _error = txt; }
};

}

#endif // MODEL_BASE_H
