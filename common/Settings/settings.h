#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include "Utils/singleton.h"
#include "include/db_connection_params.h"

namespace config
{

#define CONFIG_FILE "config.json"

/// <summary>
/// Класс настроек
/// </summary>
class Settings : public util::Singleton<Settings>
{
public:

private:
    bool _isReady = false;
    db::DbConnectionParams _configDb;

protected:
    friend class util::Singleton<Settings>;
    inline Settings& operator = (const Settings&) { return *this; }
    Settings();
    virtual ~Settings();

public:
	/// <summary>
	/// Конфигурация найдена и считана
	/// </summary>
	/// <returns>Результат чтения конфига</returns>
    bool isReady() const { return _isReady;}

	/// <summary>
    /// Чтение файла конфигурации в формате json
	/// </summary>
    void readConfig();

    /// <summary>
    /// Запись параметров в файл конфигурации в формате json
    /// </summary>
    /// <returns>Результат сохранения</returns>
    bool saveConfig();

	/// <summary>
    /// Конфигурация подключения к БД
	/// </summary>
	/// <returns>Указатель на структуру конфига</returns>
    const db::DbConnectionParams configDb() { return _configDb;}
    void setConfigDb(const db::DbConnectionParams &config);
};

}

#endif // ADPI2_SETTINGS_H
