#ifndef DB_MODEL_COUNTERS_H
#define DB_MODEL_COUNTERS_H

#include <QHash>
#include "DbModelBase/dbmodelbase.h"

namespace db {

/// <summary>
/// Модель счётчиков
/// </summary>
class DbModelCounters : public DbModelBase
{
public:
    DbModelCounters(const QString &alias, const db::DbConnectionParams &params) noexcept;
    virtual ~DbModelCounters();

    /// <summary>
    /// Создание таблицы счётчиков
    /// </summary>
    bool create() const;

    /// <summary>
    /// Выбор всех данных из таблицы счётчиков
    /// </summary>
    /// <param name="counters">Выходные значения счётчиков</param>
    bool select(QHash<QString, int> &counters) const;

    /// <summary>
    /// Добавление данных в таблицу счётчиков
    /// </summary>
    bool insert(const QHash<QString, int> &counters) const;

    /// <summary>
    /// Удаление данных всех из таблицы счётчиков
    /// </summary>
    bool removeAll() const;
};

}

#endif // DB_MODEL_COUNTERS_H
