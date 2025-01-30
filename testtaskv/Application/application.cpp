#include <QDebug>
#include <QScopedPointer>
#include "application.h"
#include "Controller/controller.h"
#include "Settings/settings.h"
#include "Widget/widget.h"
#include "include/db_connection_params.h"

using namespace config;

Application::Application(int &argc, char **argv) noexcept
    : QApplication(argc, argv)
{
}

Application::~Application()
{
}

int Application::run()
{
    Settings *settings = &Settings::Instance();
    Q_CHECK_PTR(settings);
    settings->readConfig();
    if (!settings->isReady()) {
        db::DbConnectionParams params;
        params.databasename = "counters.db";
        params.driver = "QSQLITE";
        settings->setConfigDb(params);
        settings->saveConfig();
    }

    QScopedPointer<Controller> controller(new Controller(this));
    connect(this, &Application::signalStartCountersLoop,
            controller.data(), &Controller::slotStartCountersLoop, Qt::QueuedConnection);

    QScopedPointer<Widget> window(new Widget);
    connect(window.data(), &Widget::signalAddCounter,
            controller.data(), &Controller::slotAddCounter, Qt::QueuedConnection);
    connect(window.data(), &Widget::signalDeleteCounter,
            controller.data(), &Controller::slotDeleteCounter, Qt::QueuedConnection);
    connect(window.data(), &Widget::signalSaveCounters,
            controller.data(), &Controller::slotSaveCounters, Qt::QueuedConnection);
    connect(controller.data(), &Controller::signalAddCounter,
            window.data(), &Widget::slotAddCounter, Qt::QueuedConnection);
    connect(controller.data(), &Controller::signalUpdateCounters,
            window.data(), &Widget::slotUpdateCounters, Qt::QueuedConnection);
    connect(controller.data(), &Controller::signalUpdateFrequency,
            window.data(), &Widget::slotUpdateFrequency, Qt::QueuedConnection);
    connect(controller.data(), &Controller::signalSaveResult,
            window.data(), &Widget::slotSaveResult, Qt::QueuedConnection);

    window->resize(640, 480);
    window->show();

    emit signalStartCountersLoop();

	return exec();
}

