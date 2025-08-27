#pragma once
#include <QString>
#include <QList>
#include <QMap>

// 📦 Инициализация и базовые операции
void initDatabase();
void insertEmptyRobot();
void updateRobot(int id, const QString &field, const QString &value);
void deleteRobot(int id);
QList<QMap<QString, QString>> getAllRobots();

// ➕ Добавление новой записи с данными
void insertRobot(const QString &model,
                 const QString &robot_sn,
                 const QString &controller_sn,
                 const QString &status,
                 const QString &fault_description,
                 const QString &fault_module,
                 const QString &fault_reason,
                 const QString &tasks_done,
                 const QString &tasks_required,
                 const QString &required_parts);
