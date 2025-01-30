#include <QString>
#include <QtTest>
#include <QFile>
#include "test_taskV.h"
#include "Settings/settings.h"
#include "DbModelCounters/dbmodelcounters.h"

using namespace config;
using namespace db;

Test::Test(QObject *parent)
    :QObject(parent)
{
    freopen("test_taskV.txt", "w", stdout);
}

void Test::checkTest()
{
    QVERIFY2(true, "Failure condition");
}

void Test::test_createConfigFile()
{
    // Удалить файл конфига
    QString filePath = QCoreApplication::applicationDirPath() + "/" + CONFIG_FILE; // Путь к файлу
    if (QFile::exists(filePath)) {
        bool success = QFile::remove(filePath);
        QVERIFY2(success, "Ошибка удаления конфига");
    }

    Settings *settings = &Settings::Instance();
    Q_CHECK_PTR(settings);
    settings->readConfig();
    if (!settings->isReady()) {
        db::DbConnectionParams params;
        params.databasename = "counters.db";
        params.driver = "QSQLITE";
        settings->setConfigDb(params);
        settings->saveConfig();

        // Чтение заново
        settings->readConfig();
        QVERIFY2(settings->isReady(), "Ошибка чтения конфига");
        QVERIFY2(settings->configDb().databasename == params.databasename, "Ошибка названия файла db");
        QVERIFY2(settings->configDb().driver == params.driver, "Ошибка названия драйвера db");

    } else {
        QVERIFY2(true, "Неверный этап теста 1");
    }
}

void Test::test_connectToDb()
{
    Settings *settings = &Settings::Instance();
    Q_CHECK_PTR(settings);
    settings->readConfig();
    QVERIFY2(settings->isReady(), "Ошибка чтения конфига");
    QScopedPointer<db::DbModelCounters> model(new DbModelCounters(QUuid::createUuid().toString(),
                                                                  settings->configDb()));
    QVERIFY2(model->setConnection(), "Ошибка соединения с БД");
    QVERIFY2(model->isOpen(), "Ошибка открытия файла БД");
}

void Test::test_CRUD()
{
    // Удалить файл БД
    QString filePath = QCoreApplication::applicationDirPath() + "/counters.db"; // Путь к файлу
    if (QFile::exists(filePath)) {
        QFile::remove(filePath);
    }

    Settings *settings = &Settings::Instance();
    Q_CHECK_PTR(settings);
    settings->readConfig();
    QVERIFY2(settings->isReady(), "Ошибка чтения конфига");
    QScopedPointer<db::DbModelCounters> model(new DbModelCounters(QUuid::createUuid().toString(),
                                                                  settings->configDb()));
    QVERIFY2(model->setConnection(), "Ошибка соединения с БД");
    QVERIFY2(model->isOpen(), "Ошибка открытия файла БД");

    QVERIFY2(model->create(), "Ошибка создания");
    QVERIFY2(model->removeAll(), "Ошибка очистки");

    QString id = "777";
    int value = 7;
    QHash<QString, int> counters;
    counters[id] = value;
    QVERIFY2(model->insert(counters), "Ошибка сохранения");
    QVERIFY2(model->select(counters), "Ошибка сохранения");
    bool found = false;
    foreach (QString key, counters.keys()) {
        if (counters[key] == value) {
            found = true;
            break;
        }
    }
    QVERIFY2(found, "Ошибка чтения");
}

QTEST_MAIN(Test)

