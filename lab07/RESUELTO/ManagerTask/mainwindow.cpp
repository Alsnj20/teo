#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // La conexión se hace auto por Qt por el slot
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addTaskButton_clicked() {
    qDebug() << "Botón Agregar clicado";
    Task* task = new Task(this);
    ui->tasksLayout->addWidget(task);
    mTasks.append(task);
    connect(task, &Task::removeTask, this, &MainWindow::removeTask);
}

void MainWindow::removeTask(Task* task) {
    qDebug() << "Eliminando tarea...";
    ui->tasksLayout->removeWidget(task);
    mTasks.removeOne(task);
    task->deleteLater();
}
