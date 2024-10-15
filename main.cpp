#include "mainwindow.h"

#include <QApplication>
#include <QUdpSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.initSocket();
    w.show();
    return a.exec();
}
