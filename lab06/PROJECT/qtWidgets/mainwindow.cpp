#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QApplication"
#include "QPushButton"
#include <QDebug>
// #include "task.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
