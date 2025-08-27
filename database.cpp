#include "database.h"
#include "migrations.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("robots.db");
    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе:" << db.lastError().text();
        return;
    }

    QSqlQuery q;
    q.exec("CREATE TABLE IF NOT EXISTS robots ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "model TEXT,"
           "robot_sn TEXT,"
           "controller_sn TEXT,"
           "status TEXT,"
           "fault_description TEXT,"
           "fault_module TEXT,"
           "fault_reason TEXT,"
           "tasks_done TEXT,"
           "tasks_required TEXT,"
           "required_parts TEXT,"
           "note TEXT"
           ")");

    applyMigrations(db);  // 💡 Вызов миграций
}

void insertEmptyRobot() {
    QSqlQuery q;
    q.prepare("INSERT INTO robots (model, robot_sn, controller_sn, status, fault_description, fault_module, fault_reason, tasks_done, tasks_required, required_parts, note) "
              "VALUES ('-', '', '', '-', '', '', '', '', '', '', '')");
    q.exec();
}


void insertRobot(const QString &model,
                 const QString &robot_sn,
                 const QString &controller_sn,
                 const QString &status,
                 const QString &fault_description,
                 const QString &fault_module,
                 const QString &fault_reason,
                 const QString &tasks_done,
                 const QString &tasks_required,
                 const QString &required_parts,
                 const QString &note)
{
    QSqlQuery q;
    q.prepare("INSERT INTO robots (model, robot_sn, controller_sn, status, fault_description, fault_module, fault_reason, tasks_done, tasks_required, required_parts, note) "
              "VALUES (:model, :robot_sn, :controller_sn, :status, :fault_description, :fault_module, :fault_reason, :tasks_done, :tasks_required, :required_parts, :note)");

    q.bindValue(":model", model);
    q.bindValue(":robot_sn", robot_sn);
    q.bindValue(":controller_sn", controller_sn);
    q.bindValue(":status", status);
    q.bindValue(":fault_description", fault_description);
    q.bindValue(":fault_module", fault_module);
    q.bindValue(":fault_reason", fault_reason);
    q.bindValue(":tasks_done", tasks_done);
    q.bindValue(":tasks_required", tasks_required);
    q.bindValue(":required_parts", required_parts);
    q.bindValue(":note", note);

    if (!q.exec()) {
        qDebug() << "Ошибка при добавлении робота:" << q.lastError().text();
    }
}


void updateRobot(int id, const QString &field, const QString &value) {
    QSqlQuery q;
    q.prepare(QString("UPDATE robots SET %1 = :val WHERE id = :id").arg(field));
    q.bindValue(":val", value);
    q.bindValue(":id", id);
    q.exec();
}


void deleteRobot(int id) {
    QSqlQuery q;
    q.prepare("DELETE FROM robots WHERE id = :id");
    q.bindValue(":id", id);
    q.exec();
}


QList<QMap<QString, QString>> getAllRobots() {
    QList<QMap<QString, QString>> list;
    QSqlQuery q("SELECT * FROM robots ORDER BY id");
    while (q.next()) {
        QMap<QString, QString> robot;
        robot["id"] = q.value("id").toString();
        robot["model"] = q.value("model").toString();
        robot["robot_sn"] = q.value("robot_sn").toString();
        robot["controller_sn"] = q.value("controller_sn").toString();
        robot["status"] = q.value("status").toString();
        robot["fault_description"] = q.value("fault_description").toString();
        robot["fault_module"] = q.value("fault_module").toString();
        robot["fault_reason"] = q.value("fault_reason").toString();
        robot["tasks_done"] = q.value("tasks_done").toString();
        robot["tasks_required"] = q.value("tasks_required").toString();
        robot["required_parts"] = q.value("required_parts").toString();
        robot["note"] = q.value("note").toString();
        list.append(robot);
    }
    return list;
}

