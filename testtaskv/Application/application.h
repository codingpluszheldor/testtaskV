#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

/// <summary>
/// Главный класс приложения
/// </summary>
class Application : public QApplication
{
    Q_OBJECT

private:

public:
    Application(int &argc, char **argv) noexcept;
    virtual ~Application();

    /// <summary>
    /// Запуск цикла событий
    /// </summary>
	int run();

signals:
    /// <summary>
    /// Запуск потока инкрементирования счётчиков
    /// </summary>
    void signalStartCountersLoop();
};

#endif // APPLICATION_H
