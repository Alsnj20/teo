#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Task *t = new Task;
    t->show();

    connect(ui->colorList, &QListWidget::itemClicked,
            this, [this, t](QListWidgetItem *item) {
                QString color = item->text();
                ui->colorLabel->setText("Color seleccionado: " + color);

                // Emitimos el color hacia la otra ventana
                t->actualizarColor(color);
            });
}

void MainWindow::mostrarColorSeleccionado()
{
    QString color = ui->colorList->currentItem()->text();
    ui->colorLabel->setText("Color seleccionado: " + color);
}

MainWindow::~MainWindow()
{
    delete ui;
}
