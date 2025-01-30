#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QHeaderView>

/// <summary>
/// Главное окно приложения
/// </summary>
class Widget : public QWidget
{
    Q_OBJECT

private:
    QTableWidget *_table {nullptr};
    QPushButton *_addButton {nullptr};
    QPushButton *_deleteButton {nullptr};
    QPushButton *_saveButton {nullptr};
    QLabel *_frequencyLabel {nullptr};

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    /// <summary>
    /// Добавление счётчика в таблицу
    /// </summary>
    /// <param name="uuid">ИД созданного счетчика</param>
    /// <param name="value">Значение созданного счетчика</param>
    void slotAddCounter(const QString &uuid, const int value);

    /// <summary>
    /// Удаление счётчика из таблицы
    /// </summary>
    void slotDeleteCounter();

    /// <summary>
    /// Обновление счётчиков в таблице
    /// </summary>
    /// <param name="counters">Счетчики</param>
    void slotUpdateCounters(const QHash<QString, int> &counters);

    /// <summary>
    /// Обновление частоты
    /// </summary>
    /// <param name="freq">Частота</param>
    void slotUpdateFrequency(const double &freq);

    /// <summary>
    /// Отображение результата сохранения счётчиков в БД
    /// </summary>
    /// <param name="result">Результат</param>
    void slotSaveResult(const bool &result);

signals:
    /// <summary>
    /// Добавление счётчика
    /// </summary>
    void signalAddCounter();

    /// <summary>
    /// Удаление счётчика
    /// </summary>
    /// <param name="uuid">ИД счетчика</param>
    void signalDeleteCounter(const QString &uuid);

    /// <summary>
    /// Сохранение счётчиков в БД
    /// </summary>
    void signalSaveCounters();
};
#endif // WIDGET_H
