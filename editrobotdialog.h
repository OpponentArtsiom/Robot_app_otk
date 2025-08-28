#pragma once
#include "qdatetimeedit.h"
#include <QDialog>
#include <QMap>
#include <QString>
#include <QDateTimeEdit>

class QComboBox;
class QLineEdit;
class QPlainTextEdit;
class QPushButton;

class EditRobotDialog : public QDialog {
    Q_OBJECT
public:
    EditRobotDialog(int robotId, QWidget *parent = nullptr);

private slots:
    void saveChanges();

private:
    int id;
    QDateTimeEdit *receivedAtEdit;
    QComboBox *modelBox;
    QLineEdit *robotSnEdit;
    QLineEdit *controllerSnEdit;
    QComboBox *statusBox;
    QPlainTextEdit *faultEdit;
    QPlainTextEdit *moduleEdit;
    QPlainTextEdit *reasonEdit;
    QPlainTextEdit *doneEdit;
    QPlainTextEdit *requiredEdit;
    QPlainTextEdit *partsEdit;
    QPlainTextEdit *noteEdit;

    void loadRobotData();
};

