#ifndef DB_CONNECTION_H_INCLUDED
#define DB_CONNECTION_H_INCLUDED

#include <QtSql>
#include <QString>

namespace db {

#define TIMEOUT_RECONNECT 5000

/// <summary>
/// Соединение с базой данных
/// </summary>
class DbConnection
{
private:
    QString _alias;
    QString _hostname;
    QString _driver;
    quint16 _port;
    QString _databasename;
    QString _username;
    QString _password;

public:
    DbConnection(const QString &alias,
                 const QString &hostname,
                 const QString &driver,
                 const quint16 &port,
                 const QString &databasename,
                 const QString &username,
                 const QString &password) noexcept;
    virtual ~DbConnection();

    /// <summary>
    /// Открыть соединение
    /// </summary>
    /// <returns>Результат</returns>
    bool open() const;

    /// <summary>
    /// Закрыть соединение
    /// </summary>
    /// <returns>Результат</returns>
    void close() const;

    /// <summary>
    /// Закрыть соединение
    /// </summary>
    /// <param name="alias">Название соединения</param>
    /// <returns>Результат</returns>
    static void close(const QString &alias);

    /// <summary>
    /// Проверка соединения
    /// </summary>
    /// <returns>Результат</returns>
    static bool isOpen(const QString &alias);

    /// <summary>
    /// Повторное соединение
    /// </summary>
    /// <param name="count">Количество попыток соединения</param>
    /// <returns>Результат</returns>
    bool reConnect(const quint16 &count) const;

    /// <summary>
    /// Возвращает текст ошибки
    /// </summary>
    /// <returns>Текст ошибки</returns>
    [[nodiscard]]
    QString error() const;
};

}

#endif // DB_CONNECTION_H_INCLUDED
