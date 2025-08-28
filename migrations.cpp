#include "migrations.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int getCurrentSchemaVersion(QSqlDatabase& db) {
    QSqlQuery q(db);
    if (!q.exec("SELECT version FROM schema_version LIMIT 1")) {
        return 0; // Таблица не существует или пуста
    }
    if (q.next()) {
        return q.value(0).toInt();
    }
    return 0;
}

void applyMigrations(QSqlDatabase& db) {
    QSqlQuery q(db);

    // Создание таблицы версий, если её нет
    q.exec("CREATE TABLE IF NOT EXISTS schema_version (version INTEGER NOT NULL)");

    int version = getCurrentSchemaVersion(db);

    if (version == 0) {
        q.exec("INSERT INTO schema_version (version) VALUES (1)");
        version = 1;
    }

    // 🔄 Миграция до версии 2: добавление поля location
    if (version < 2) {
        qDebug() << "Применяется миграция до версии 2: добавление поля location";
        if (!q.exec("ALTER TABLE robots ADD COLUMN location TEXT")) {
            qDebug() << "Ошибка миграции:" << q.lastError().text();
        }
        q.exec("UPDATE schema_version SET version = 2");
    }

    if (version < 3) {
    qDebug() << "Миграция до версии 3: добавление поля received_at после id";

    QSqlQuery q(db);

    // Переименовываем старую таблицу
    q.exec("ALTER TABLE robots RENAME TO robots_old");

    // Создаём новую таблицу с нужным порядком колонок
    q.exec(R"(
        CREATE TABLE robots (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            received_at TEXT,
            model TEXT,
            robot_sn TEXT,
            controller_sn TEXT,
            status TEXT,
            fault_description TEXT,
            fault_module TEXT,
            fault_reason TEXT,
            tasks_done TEXT,
            tasks_required TEXT,
            required_parts TEXT,
            note TEXT
        )
    )");

    // Копируем данные, заполняя received_at пустым значением
    q.exec(R"(
        INSERT INTO robots (
            id, received_at, model, robot_sn, controller_sn, status,
            fault_description, fault_module, fault_reason,
            tasks_done, tasks_required, required_parts, note
        )
        SELECT
            id, '', model, robot_sn, controller_sn, status,
            fault_description, fault_module, fault_reason,
            tasks_done, tasks_required, required_parts, note
        FROM robots_old
    )");

    // Удаляем старую таблицу
    q.exec("DROP TABLE robots_old");

    // Обновляем версию схемы
    q.exec("UPDATE schema_version SET version = 3");
}

}

