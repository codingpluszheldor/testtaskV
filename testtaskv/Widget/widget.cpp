#include <QDebug>
#include <QMessageBox>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Таблица счётчиков"));

    QVBoxLayout *layout = new QVBoxLayout(this);

    _table = new QTableWidget(0, 1, this);
    _table->setHorizontalHeaderLabels(QStringList() << tr("Счётчик"));
    _table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    _table->setSelectionBehavior(QAbstractItemView::SelectRows);
    _table->setSelectionMode(QAbstractItemView::SingleSelection);
    _table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(_table);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    _addButton = new QPushButton(tr("Добавить"), this);
    connect(_addButton, &QPushButton::clicked, this, [this]() {
        emit signalAddCounter(); }, Qt::QueuedConnection);
    _deleteButton = new QPushButton(tr("Удалить"), this);
    connect(_deleteButton, &QPushButton::clicked, this, &Widget::slotDeleteCounter, Qt::QueuedConnection);
    _saveButton = new QPushButton(tr("Сохранить"), this);
    connect(_saveButton, &QPushButton::clicked, this, [this]() {
        emit signalSaveCounters(); }, Qt::QueuedConnection);

    buttonLayout->addWidget(_addButton);
    buttonLayout->addWidget(_deleteButton);
    buttonLayout->addWidget(_saveButton);

    layout->addLayout(buttonLayout);

    _frequencyLabel = new QLabel(tr("Частота: 0"), this);
    layout->addWidget(_frequencyLabel);
}

Widget::~Widget()
{
    if (_table != nullptr) delete _table;
    if (_addButton != nullptr) delete _addButton;
    if (_deleteButton != nullptr) delete _deleteButton;
    if (_saveButton != nullptr) delete _saveButton;
    if (_frequencyLabel != nullptr) delete _frequencyLabel;
}

void Widget::slotAddCounter(const QString &uuid, const int value)
{
    int row = _table->rowCount();
    _table->insertRow(row);
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(value));
    item->setData(Qt::UserRole, uuid);
    _table->setItem(row, 0, item);
    qDebug() << __FUNCTION__;
}

void Widget::slotDeleteCounter()
{
    int row = _table->currentRow();
    if (row >= 0) {
        QString uuid = _table->item(row, 0)->data(Qt::UserRole).toString();
        _table->removeRow(row);
        _table->clearSelection();
        _table->setCurrentCell(-1, -1);
        emit signalDeleteCounter(uuid);
    }
    qDebug() << __FUNCTION__;
}

void Widget::slotUpdateCounters(const QHash<QString, int> &counters)
{
    int rowCount = _table->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QString key = _table->item(i, 0)->data(Qt::UserRole).toString();
        if (counters.contains(key)) {
            _table->item(i, 0)->setText(QString::number(counters.value(key)));
        }
    }
    qDebug() << __FUNCTION__;
}

void Widget::slotUpdateFrequency(const double &freq)
{
    _frequencyLabel->setText(QString("Частота: %1").arg(QString::number(freq, 'f', 1)));
    qDebug() << __FUNCTION__;
}

void Widget::slotSaveResult(const bool &result)
{
    if (result) {
        QMessageBox::information(this, tr("Сохранено"), tr("Счётчики сохранены в БД!"));
    } else {
        QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка при сохранении в БД!"));
    }
}
