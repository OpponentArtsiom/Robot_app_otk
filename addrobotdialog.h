#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>

class AddRobotDialog : public QDialog {
    Q_OBJECT
public:
    AddRobotDialog(QWidget *parent = nullptr);

    QString getField(const QString &name) const;

private:
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
};

