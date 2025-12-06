#ifndef TASK_H
#define TASK_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Task; }
QT_END_NAMESPACE

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();

public slots:
    void recibirMensaje(const QString &texto);  // <-- slot que recibirá el mensaje

private:
    Ui::Task *ui;
};

#endif // TASK_H
