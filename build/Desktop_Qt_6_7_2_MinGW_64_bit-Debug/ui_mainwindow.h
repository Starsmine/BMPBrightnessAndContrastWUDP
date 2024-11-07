/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_3;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *TransferPhoto;
    QPushButton *TransferOverlay;
    QCheckBox *checkBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(977, 455);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(60, 310, 181, 51));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(60, 360, 181, 51));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 10, 49, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(360, 10, 49, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(660, 10, 49, 16));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(300, 320, 160, 22));
        horizontalSlider->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(300);
        horizontalSlider->setValue(100);
        horizontalSlider->setSliderPosition(100);
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setGeometry(QRect(520, 320, 160, 22));
        horizontalSlider_2->setMinimum(-20);
        horizontalSlider_2->setMaximum(100);
        horizontalSlider_2->setValue(0);
        horizontalSlider_2->setSliderPosition(0);
        horizontalSlider_2->setOrientation(Qt::Orientation::Horizontal);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(310, 340, 71, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(540, 340, 49, 16));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(800, 330, 171, 51));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(60, 40, 281, 251));
        label_6->setScaledContents(true);
        label_6->setIndent(-4);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(360, 40, 281, 251));
        label_7->setScaledContents(true);
        label_7->setIndent(-4);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(650, 40, 281, 251));
        label_8->setScaledContents(true);
        label_8->setIndent(-4);
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(310, 360, 75, 24));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(540, 360, 75, 24));
        TransferPhoto = new QPushButton(centralwidget);
        TransferPhoto->setObjectName("TransferPhoto");
        TransferPhoto->setGeometry(QRect(700, 310, 101, 41));
        TransferOverlay = new QPushButton(centralwidget);
        TransferOverlay->setObjectName("TransferOverlay");
        TransferOverlay->setGeometry(QRect(700, 350, 101, 41));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(820, 380, 131, 20));
        checkBox->setTristate(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 977, 22));
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
        pushButton->setText(QCoreApplication::translate("MainWindow", "Load Photo", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Load Overlay", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Photo", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Overlay", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Output", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Brightness", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Contrast", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Save Output", nullptr));
        label_6->setText(QString());
        label_7->setText(QString());
        label_8->setText(QString());
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        TransferPhoto->setText(QCoreApplication::translate("MainWindow", "Transfer Photo", nullptr));
        TransferOverlay->setText(QCoreApplication::translate("MainWindow", "Transfer Overlay", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Toggle Overlay", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
