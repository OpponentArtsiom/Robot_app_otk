#pragma once
#include "qdatetime.h"
#include "qplaintextedit.h"
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDateTimeEdit>

class AddRobotDialog : public QDialog {
    Q_OBJECT
public:
    AddRobotDialog(QWidget *parent = nullptr);

    QString getField(const QString &name) const;

private:
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
};

