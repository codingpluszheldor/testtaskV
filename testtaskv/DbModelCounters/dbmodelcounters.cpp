#include <QUuid>
#include "dbmodelcounters.h"

using namespace db;

DbModelCounters::DbModelCounters(const QString &alias, const DbConnectionParams &params) noexcept
    : DbModelBase(alias, params)
{    
}

DbModelCounters::~DbModelCounters()
{

}

bool DbModelCounters::create() const
{
    QSqlDatabase db = QSqlDatabase::database(_alias);
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS counters (value INTEGER)");
    query.exec();

    if (query.lastError().isValid()) {
        _error += query.lastError().text() + "\n";
        return false;
    }

    return true;
}

bool DbModelCounters::select(QHash<QString, int> &counters) const
{
    counters.clear();
    QSqlDatabase db = QSqlDatabase::database(_alias);
    _error.clear();

    QSqlQuery query(db);
    query.prepare("SELECT value FROM counters");
    query.exec();

    int value = query.record().indexOf("value");

    if (query.lastError().isValid()) {
        _error += query.lastError().text() + "\n";
        return false;
    }

    while (query.next()) {
        counters.insert(QUuid::createUuid().toString(), query.value(value).toInt());
    }
    return true;
}

bool DbModelCounters::insert(const QHash<QString, int> &counters) const
{
    if (counters.isEmpty()) {
        return true;
    }

    QSqlDatabase db = QSqlDatabase::database(_alias);
    _error.clear();
    if (db.transaction()) {
        foreach (QString key, counters.keys())
        {
            QSqlQuery query(db);
            query.prepare("INSERT INTO counters (value) "
                          "VALUES (:value) ");
            query.bindValue(":value", counters[key]);
            query.exec();
            if (query.lastError().isValid()) {
                _error += query.lastError().text() + "\n";
            }
        }

        if (!db.commit()) {
            _error = "Error commit transaction";
            db.rollback();
        }
    } else {
        _error = "Error start transaction";
    }

    return _error.isEmpty();
}

bool DbModelCounters::removeAll() const
{
    QSqlDatabase db = QSqlDatabase::database(_alias);
    QSqlQuery query(db);
    query.prepare("DELETE FROM counters");
    query.exec();

    if (query.lastError().isValid()) {
        _error += query.lastError().text() + "\n";
        return false;
    }

    return true;
}
