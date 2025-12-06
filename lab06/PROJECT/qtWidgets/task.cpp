#include "mainwindow.h"
#include "task.h"
#include "QPushButton"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addTaskButton, &QPushButton::clicked, this, [this]() {
        Task *t = new Task(this);
        t->show(); // Muestra el widget de tarea
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
