/********************************************************************************
** Form generated from reading UI file 'task.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_H
#define UI_TASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Task
{
public:
    QDialogButtonBox *buttonBox;
    QCheckBox *checkBox;
    QLineEdit *MiText;

    void setupUi(QDialog *Task)
    {
        if (Task->objectName().isEmpty())
            Task->setObjectName("Task");
        Task->resize(400, 300);
        buttonBox = new QDialogButtonBox(Task);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        checkBox = new QCheckBox(Task);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(70, 220, 61, 21));
        MiText = new QLineEdit(Task);
        MiText->setObjectName("MiText");
        MiText->setGeometry(QRect(140, 180, 113, 26));

        retranslateUi(Task);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Task, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Task, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Task);
    } // setupUi

    void retranslateUi(QDialog *Task)
    {
        Task->setWindowTitle(QCoreApplication::translate("Task", "Dialog", nullptr));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Task: public Ui_Task {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_H
