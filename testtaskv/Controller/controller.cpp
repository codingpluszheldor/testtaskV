#include <QDebug>
#include <QUuid>
#include "controller.h"
#include "Settings/settings.h"

using namespace config;
using namespace db;

Controller::Controller(QObject *parent) noexcept
    : QObject{parent}
{
    Settings *settings = &Settings::Instance();
    Q_CHECK_PTR(settings);
    _model.reset(new DbModelCounters(QUuid::createUuid().toString(),
                                     settings->configDb()));
}

Controller::~Controller()
{
    _running = false;
    if (_incThread.joinable()) {
        _incThread.join();
    }

    // Сохранение счётчиков перед закрытием программы
    slotSaveCounters();
}

void Controller::slotStartCountersLoop()
{
    if (!_model->isOpen() && !_model->setConnection()) {
        qCritical() << __FUNCTION__ << _model->errorText();
    } else {
        if (!_model->create()) {
            qCritical() << __FUNCTION__ << _model->errorText();
        }

        // Загрузка счётчиков при запуске
        if (_model->select(_counters)) {
            _sumCounters = 0;
            foreach (QString key, _counters.keys()) {
                _sumCounters += _counters[key];
                emit signalAddCounter(key, _counters[key]);
                qDebug() << key << ":" << _counters[key];
            }
        } else {
            qCritical() << __FUNCTION__ << _model->errorText();
        }
    }

    _incThread = std::thread([this]() {
        using namespace std::chrono_literals;
        while (_running) {
            std::this_thread::sleep_for(1s);
            incrementCounters();
            calculateFrequency();
            emit signalUpdateCounters(_counters);
            qDebug() << "Next loop";
        }
    });
}

void Controller::incrementCounters()
{
    QMutexLocker locker(&_mutex);
    _sumCounters = 0;
    foreach (QString key, _counters.keys()) {
        _counters[key]++;
        _sumCounters += _counters[key];
        qDebug() << key << ":" << _counters[key];
    }
    qDebug() << "sum:" << _sumCounters;
}

void Controller::calculateFrequency()
{
    QMutexLocker locker(&_mutex);

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    int deltaSum = _sumCounters - _lastSum;

    std::chrono::duration<double> elapsedSeconds = now - _lastTime;
    double frequency = static_cast<double>(deltaSum) / elapsedSeconds.count();
    if (frequency < 0.0) {
        frequency = _lastFrequency;
    }
    _lastFrequency = frequency;
    emit signalUpdateFrequency(frequency);

    _lastSum = _sumCounters;
    _lastTime = now;
}

void Controller::slotAddCounter()
{
    QMutexLocker locker(&_mutex);
    QString uuid = QUuid::createUuid().toString();
    _counters.insert(uuid, 0);
    emit signalAddCounter(uuid, 0);
    qDebug() << __FUNCTION__;
}

void Controller::slotDeleteCounter(const QString &uuid)
{
    QMutexLocker locker(&_mutex);
    if (_counters.contains(uuid)) {
        _sumCounters -= _counters[uuid];
        _counters.remove(uuid);
        qDebug() << "sum:" << _sumCounters;
    }
    qDebug() << __FUNCTION__;
}

void Controller::slotSaveCounters()
{
    qDebug() << __FUNCTION__;
    QMutexLocker locker(&_mutex);

    if (!_model->isOpen() && !_model->setConnection()) {
        qCritical() << __FUNCTION__ << _model->errorText();
        return;
    }

    if (_model->removeAll() && _model->insert(_counters)) {
        emit signalSaveResult(true);
        qDebug() << __FUNCTION__ << "Сохранено:" << _counters.count();
    } else {
        emit signalSaveResult(false);
        qCritical() << __FUNCTION__ << _model->errorText();
    }
}
