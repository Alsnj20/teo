#include "task.h"
#include "../ui_task.h"
#include <QDebug>

Task::Task(QWidget* parent) : QWidget(parent), ui(new Ui::Task) {
    ui->setupUi(this);
    connect(ui->removeButton, &QPushButton::clicked, this, &Task::on_removeButton_clicked);
}

Task::~Task() {
    delete ui;
}

void Task::on_removeButton_clicked() {
    qDebug() << "Eliminar tarea emitida";
    emit removeTask(this);
}
