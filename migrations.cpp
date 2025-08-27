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

    // Добавляй новые миграции ниже:
    // if (version < 3) { ... }
}

