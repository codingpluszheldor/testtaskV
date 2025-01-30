#ifndef TEST_H
#define TEST_H

#include <QObject>

class Test: public QObject
{
	Q_OBJECT

public:
    Test(QObject *parent = nullptr);

private Q_SLOTS:
    void checkTest();

    void test_createConfigFile();

    void test_connectToDb();

    void test_CRUD();
};

#endif // TEST_H
