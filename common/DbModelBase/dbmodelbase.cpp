#include "dbmodelbase.h"

using namespace db;

DbModelBase::DbModelBase(const QString &alias, const DbConnectionParams &params) noexcept
    : _alias{alias},
      _params{params}
{
}

DbModelBase::~DbModelBase()
{
    qDebug() << "ModelBase::closeConnection:" << _alias;
    closeConnection();
}

bool DbModelBase::setConnection() noexcept
{
    DbConnection dbcntor(_alias,
                         _params.hostname,
                         _params.driver,
                         _params.port,
                         _params.databasename,
                         _params.username,
                         _params.password);
    if (!dbcntor.open()) {
        _error = dbcntor.error();
        return false;
    }

    return true;
}

void DbModelBase::closeConnection()
{
    DbConnection::close(_alias);
}

bool DbModelBase::isOpen() const
{
     return DbConnection::isOpen(_alias);
}
