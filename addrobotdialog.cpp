#include "addrobotdialog.h"
#include "qplaintextedit.h"

AddRobotDialog::AddRobotDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Добавить нового робота");
    setFixedSize(600, 500);

    modelBox = new QComboBox();
    modelBox->addItems({"RC3", "RC5", "RC10", "-"});

    robotSnEdit = new QLineEdit();
    controllerSnEdit = new QLineEdit();

    statusBox = new QComboBox();
    statusBox->addItems({"Необходим ремонт", "Тестируется", "Протестирован", "Откалиброван", "Упакован", "-"});
   
    receivedAtEdit = new QDateTimeEdit();
    receivedAtEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    receivedAtEdit->setCalendarPopup(true);
    receivedAtEdit->setDateTime(QDateTime::currentDateTime());




    faultEdit = new QPlainTextEdit();
    moduleEdit = new QPlainTextEdit();
    reasonEdit = new QPlainTextEdit();
    doneEdit = new QPlainTextEdit();
    requiredEdit = new QPlainTextEdit();
    partsEdit = new QPlainTextEdit();
    noteEdit = new QPlainTextEdit();

    QFormLayout *form = new QFormLayout();
    form->addRow("Дата/Время", receivedAtEdit);
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
    form->addRow("Примечание:", noteEdit);

    QPushButton *ok = new QPushButton("✅ Добавить");
    QPushButton *cancel = new QPushButton("❌ Отмена");
    connect(ok, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addStretch();
    buttons->addWidget(ok);
    buttons->addWidget(cancel);

    QVBoxLayout *main = new QVBoxLayout(this);
    main->addLayout(form);
    main->addLayout(buttons);
}

QString AddRobotDialog::getField(const QString &name) const {
    if (name == "received_at") return receivedAtEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    if (name == "model") return modelBox->currentText();
    if (name == "robot_sn") return robotSnEdit->text();
    if (name == "controller_sn") return controllerSnEdit->text();
    if (name == "status") return statusBox->currentText();
    if (name == "fault_description") return faultEdit->toPlainText();
    if (name == "fault_module") return moduleEdit->toPlainText();
    if (name == "fault_reason") return reasonEdit->toPlainText();
    if (name == "tasks_done") return doneEdit->toPlainText();
    if (name == "tasks_required") return requiredEdit->toPlainText();
    if (name == "required_parts") return partsEdit->toPlainText();
    if (name == "note") return noteEdit->toPlainText();


    return "";
}

