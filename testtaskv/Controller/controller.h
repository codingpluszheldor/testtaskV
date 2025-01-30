#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QHash>
#include <QMutex>
#include <QMutexLocker>
#include <QScopedPointer>
#include <thread>
#include <atomic>
#include <chrono>
#include "DbModelCounters/dbmodelcounters.h"

/// <summary>
/// Контроллер приложения
/// </summary>
class Controller : public QObject
{
    Q_OBJECT

private:
    QHash<QString, int> _counters; // Счётчики: key - uuid, value - текущее значение
    QMutex _mutex;
    std::atomic<bool> _running {true};
    std::thread _incThread;
    std::chrono::steady_clock::time_point _lastTime = std::chrono::steady_clock::now();
    int _sumCounters = 0;
    int _lastSum = 0;
    double _lastFrequency = 0.0;
    QScopedPointer<db::DbModelCounters> _model;

public:
    explicit Controller(QObject *parent = 0) noexcept;
    ~Controller();

private:
    /// <summary>
    /// Инкрементирование счётчиков
    /// </summary>
    void incrementCounters();

    /// <summary>
    /// Подсчёт частоты инкрементирования счётчиков
    /// </summary>
    void calculateFrequency();

public slots:
    /// <summary>
    /// Запуск потока инкрементирования счётчиков
    /// </summary>
    void slotStartCountersLoop();

    /// <summary>
    /// Добавление счётчика
    /// </summary>
    void slotAddCounter();

    /// <summary>
    /// Удаление счётчика
    /// </summary>
    /// <param name="uuid">ИД счетчика</param>
    void slotDeleteCounter(const QString &uuid);

    /// <summary>
    /// Сохранение счётчиков в БД
    /// </summary>
    void slotSaveCounters();

signals:
    /// <summary>
    /// Добавление счётчика в таблицу
    /// </summary>
    /// <param name="uuid">ИД созданного счетчика</param>
    /// <param name="value">Значение созданного счетчика</param>
    void signalAddCounter(const QString &uuid, const int value);

    /// <summary>
    /// Обновление счётчиков в таблице
    /// </summary>
    /// <param name="counters">Счетчики</param>
    void signalUpdateCounters(const QHash<QString, int> &counters);

    /// <summary>
    /// Обновление частоты
    /// </summary>
    /// <param name="freq">Частота</param>
    void signalUpdateFrequency(const double &freq);

    /// <summary>
    /// Результат сохранения счётчиков в БД
    /// </summary>
    /// <param name="result">Результат</param>
    void signalSaveResult(const bool &result);
};

#endif // CONTROLLER_H
