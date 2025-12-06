#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "task.h"
#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_addTaskButton_clicked();
    void removeTask(Task* task);

private:
    Ui::MainWindow* ui;
    QVector<Task*> mTasks;
};

#endif // MAINWINDOW_H
