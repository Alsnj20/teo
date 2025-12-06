#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class Task;
}

class Task : public QWidget {
    Q_OBJECT

public:
    explicit Task(QWidget* parent = nullptr);
    ~Task();

signals:
    void removeTask(Task* task);

private slots:
    void on_removeButton_clicked();

private:
    Ui::Task* ui;
};

#endif // TASK_H

