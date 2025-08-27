#pragma once
#include "qpushbutton.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QStringList>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addRobot();
    void deleteRobot();
    void changeRobot();
    void loadData();
    void refreshTable();

private:
    QTableWidget *table;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *changeButton;
    QPushButton *refreshButton;
    QStringList headers;
};
