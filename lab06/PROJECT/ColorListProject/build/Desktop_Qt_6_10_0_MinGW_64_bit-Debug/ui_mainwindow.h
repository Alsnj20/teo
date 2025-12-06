/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *colorList;
    QLabel *colorLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        colorList = new QListWidget(centralwidget);
        new QListWidgetItem(colorList);
        new QListWidgetItem(colorList);
        new QListWidgetItem(colorList);
        new QListWidgetItem(colorList);
        new QListWidgetItem(colorList);
        new QListWidgetItem(colorList);
        colorList->setObjectName("colorList");
        colorList->setGeometry(QRect(50, 60, 421, 231));
        colorList->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        colorLabel = new QLabel(centralwidget);
        colorLabel->setObjectName("colorLabel");
        colorLabel->setGeometry(QRect(170, 310, 251, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));

        const bool __sortingEnabled = colorList->isSortingEnabled();
        colorList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = colorList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "Rojo", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = colorList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "Verde", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = colorList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "Azul", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = colorList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("MainWindow", "Amarillo", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = colorList->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("MainWindow", "Morado", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = colorList->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("MainWindow", "New Item", nullptr));
        colorList->setSortingEnabled(__sortingEnabled);

        colorLabel->setText(QCoreApplication::translate("MainWindow", "Selecciona un color: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
