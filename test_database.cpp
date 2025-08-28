#include <QtTest/QtTest>
#include "database.h"

class DatabaseTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();       // вызывается один раз перед всеми тестами
    void testInsertRobot();    // тест на добавление
    void testUpdateRobot();    // тест на обновление
    void testDeleteRobot();    // тест на удаление
    void cleanupTestCase();    // вызывается один раз после всех тестов
};

void DatabaseTest::initTestCase() {
    initDatabase();
}

void DatabaseTest::testInsertRobot() {
    insertRobot("TestModel", "SN001", "CTRL001", "OK", "desc", "mod", "reason", "10", "20", "parts", "note", "2025-08-27T16:45:00");
    auto robots = getAllRobots();
    QVERIFY(!robots.isEmpty());
    QCOMPARE(robots.last()["model"], QString("TestModel"));
}

void DatabaseTest::testUpdateRobot() {
    auto robots = getAllRobots();
    int id = robots.last()["id"].toInt();
    updateRobot(id, "status", "Updated");
    auto updated = getAllRobots().last();
    QCOMPARE(updated["status"], QString("Updated"));
}

void DatabaseTest::testDeleteRobot() {
    auto robots = getAllRobots();
    int id = robots.last()["id"].toInt();
    deleteRobot(id);
    auto after = getAllRobots();
    QVERIFY(std::none_of(after.begin(), after.end(), [id](const QMap<QString, QString>& r) {
        return r["id"].toInt() == id;
    }));
}

void DatabaseTest::cleanupTestCase() {
    // можно очистить тестовые записи, если нужно
}

QTEST_MAIN(DatabaseTest)
#include "test_database.moc"
