#include "editrobotdialog.h"
#include "database.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QMessageBox>

EditRobotDialog::EditRobotDialog(int robotId, QWidget *parent)
    : QDialog(parent), id(robotId)
{
    setWindowTitle("Редактировать робота");

    modelBox = new QComboBox();
    modelBox->addItems({"RC3", "RC5", "RC10", "-"});

    robotSnEdit = new QLineEdit();
    controllerSnEdit = new QLineEdit();

    statusBox = new QComboBox();
    statusBox->addItems({"Необходим ремонт", "Тестируется", "Протестирован", "Откалиброван", "Упакован", "-"});

    faultEdit = new QPlainTextEdit();
    moduleEdit = new QPlainTextEdit();
    reasonEdit = new QPlainTextEdit();
    doneEdit = new QPlainTextEdit();
    requiredEdit = new QPlainTextEdit();
    partsEdit = new QPlainTextEdit();

    QFormLayout *form = new QFormLayout();
    form->addRow("Модель:", modelBox);
    form->addRow("Серийный № робота:", robotSnEdit);
    form->addRow("Серийный № контроллера:", controllerSnEdit);
    form->addRow("Статус:", statusBox);
    form->addRow("Описание неисправности:", faultEdit);
    form->addRow("Проблемный узел:", moduleEdit);
    form->addRow("Причина поломки:", reasonEdit);
    form->addRow("Проведённые работы:", doneEdit);
    form->addRow("Планируемые работы:", requiredEdit);
    form->addRow("Необходимые запчасти:", partsEdit);

    QPushButton *saveBtn = new QPushButton("💾 Сохранить");
    QPushButton *cancelBtn = new QPushButton("❌ Отмена");
    connect(saveBtn, &QPushButton::clicked, this, &EditRobotDialog::saveChanges);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addStretch();
    buttons->addWidget(saveBtn);
    buttons->addWidget(cancelBtn);

    QVBoxLayout *main = new QVBoxLayout(this);
    main->addLayout(form);
    main->addLayout(buttons);

    loadRobotData();
}

void EditRobotDialog::loadRobotData() {
    auto robots = getAllRobots();
    for (const auto &r : robots) {
        if (r["id"].toInt() == id) {
            modelBox->setCurrentText(r["model"]);
            robotSnEdit->setText(r["robot_sn"]);
            controllerSnEdit->setText(r["controller_sn"]);
            statusBox->setCurrentText(r["status"]);
            faultEdit->setPlainText(r["fault_description"]);
            moduleEdit->setPlainText(r["fault_module"]);
            reasonEdit->setPlainText(r["fault_reason"]);
            doneEdit->setPlainText(r["tasks_done"]);
            requiredEdit->setPlainText(r["tasks_required"]);
            partsEdit->setPlainText(r["required_parts"]);
            break;
        }
    }
}

void EditRobotDialog::saveChanges() {
    updateRobot(id, "model", modelBox->currentText());
    updateRobot(id, "robot_sn", robotSnEdit->text());
    updateRobot(id, "controller_sn", controllerSnEdit->text());
    updateRobot(id, "status", statusBox->currentText());
    updateRobot(id, "fault_description", faultEdit->toPlainText());
    updateRobot(id, "fault_module", moduleEdit->toPlainText());
    updateRobot(id, "fault_reason", reasonEdit->toPlainText());
    updateRobot(id, "tasks_done", doneEdit->toPlainText());
    updateRobot(id, "tasks_required", requiredEdit->toPlainText());
    updateRobot(id, "required_parts", partsEdit->toPlainText());

    QMessageBox::information(this, "Готово", "✅ Изменения сохранены.");
    accept();
}

