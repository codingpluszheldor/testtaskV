#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QVariantMap>
#include "settings.h"

using namespace config;

Settings::Settings()
{
}

Settings::~Settings()
{
}

void Settings::readConfig()
{
    if (!QFile::exists(QCoreApplication::applicationDirPath() + "/" + CONFIG_FILE))	{
        qWarning() << __FUNCTION__ << ":Файл конфигурации не найден:" << CONFIG_FILE;
        _isReady = false;
        return;
	}

    QFile file(QCoreApplication::applicationDirPath() + "/" + CONFIG_FILE);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << __FUNCTION__ << "Ошибка чтения настроек из файла:" << CONFIG_FILE;
        _isReady = false;
        return;
    }

    QByteArray buffer = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(buffer);
    if (document.isNull()) {
        qCritical() << __FUNCTION__ << "Ошибка структуры файла:" << CONFIG_FILE;
        _isReady = false;
        return;
    }

    QJsonObject jsonObj = document.object();
    _configDb.databasename = jsonObj.value("database").toObject().value("name").toString();
    _configDb.hostname = jsonObj.value("database").toObject().value("host").toString();
    _configDb.username = jsonObj.value("database").toObject().value("user").toString();
    _configDb.password = jsonObj.value("database").toObject().value("password").toString();
    _configDb.driver = jsonObj.value("database").toObject().value("driver").toString();
    _configDb.port = jsonObj.value("database").toObject().value("port").toInt();

    _isReady = true;
}

bool Settings::saveConfig()
{
    QFile file(QCoreApplication::applicationDirPath() + "/" + CONFIG_FILE);
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << __FUNCTION__ << "Ошибка открытия для записи файла конфигурации:" << CONFIG_FILE;
        return false;
    }

    QJsonObject jsonConfig;

    // Секция database
    QJsonObject database;
    database.insert("name", _configDb.databasename);
    database.insert("host", _configDb.hostname);
    database.insert("driver", _configDb.driver);
    database.insert("user", _configDb.username);
    database.insert("password", _configDb.password);
    database.insert("port", _configDb.port);
    jsonConfig.insert("database", database);

    QJsonDocument doc(jsonConfig);
    QByteArray ba = doc.toJson(QJsonDocument::Indented);
    qint64 wsz = file.write(ba);
    if (ba.size() != wsz) {
        qCritical() << __FUNCTION__ << "Ошибка записи файла конфигурации:" << CONFIG_FILE;
        file.flush();
        file.close();
        return false;
    }

    file.flush();
    file.close();
    return true;
}

void Settings::setConfigDb(const db::DbConnectionParams &config)
{
    _configDb = config;
}

