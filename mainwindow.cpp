#include "mainwindow.h"
#include "database.h"
#include "addrobotdialog.h"
#include "editrobotdialog.h"
#include "qdialog.h"
#include "qpushbutton.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    table = new QTableWidget(this);
    headers = QStringList{
        "id", "received_at", "model", "robot_sn", "controller_sn",
        "status", "fault_description", "fault_module",
        "fault_reason", "tasks_done", "tasks_required", "required_parts", "note"
    };
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels({
        "ID", "Дата/Время" , "Модель", "Серийный № робота", "Серийный № контроллера",
        "Текущий статус", "Описание неисправности", "Проблемный узел/модуль",
        "Причина поломки", "Проведенные работы", "Планируемые работы", "Необходимые запчасти", "Примечание"
    });
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    addButton = new QPushButton("➕ Добавить");
    deleteButton = new QPushButton("🗑️ Удалить");
    changeButton = new QPushButton("✏️ Изменить");
    refreshButton = new QPushButton("🔄Обновить");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(changeButton);
    buttonLayout->addWidget(refreshButton);

    layout->addWidget(table);
    layout->addLayout(buttonLayout);

    setCentralWidget(central);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addRobot);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteRobot);
    connect(changeButton, &QPushButton::clicked, this, &MainWindow::changeRobot);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshTable);

    initDatabase();
    loadData();
}

MainWindow::~MainWindow() {}

void MainWindow::loadData() {
    table->clearContents();
    auto robots = getAllRobots();
    table->setRowCount(robots.size());

    for (int row = 0; row < robots.size(); ++row) {
        const auto &robot = robots[row];
        for (int col = 0; col < headers.size(); ++col) {
            QString key = headers[col];
            QTableWidgetItem *item = new QTableWidgetItem(robot[key]);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            table->setItem(row, col, item);
        }
    }

    table->resizeColumnsToContents();
    table->resizeRowsToContents();
}

void MainWindow::addRobot() {
    AddRobotDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        insertRobot(
            dialog.getField("model"),
            dialog.getField("robot_sn"),
            dialog.getField("controller_sn"),
            dialog.getField("status"),
            dialog.getField("fault_description"),
            dialog.getField("fault_module"),
            dialog.getField("fault_reason"),
            dialog.getField("tasks_done"),
            dialog.getField("tasks_required"),
            dialog.getField("required_parts"),
            dialog.getField("note"),
            dialog.getField("received_at")
        );
        loadData();
    }
}

void MainWindow::refreshTable() {
    loadData();
    QMessageBox::information(this, "Обновлено", "🔄 Таблица успешно перезагружена.");
}


void MainWindow::deleteRobot() {
    int row = table->currentRow();
    if (row < 0) return;

    int id = table->item(row, 0)->text().toInt();
    auto reply = QMessageBox::question(this, "Удаление", "Удалить выбранного робота?");
    if (reply == QMessageBox::Yes) {
        ::deleteRobot(id);
        loadData();
    }
}

void MainWindow::changeRobot() {
    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Выбор", "Выберите строку для редактирования.");
        return;
    }

    int id = table->item(row, 0)->text().toInt();
    EditRobotDialog dialog(id, this);
    if (dialog.exec() == QDialog::Accepted) {
        loadData();
    }
}
