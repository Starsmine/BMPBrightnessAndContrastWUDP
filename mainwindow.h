#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initSocket();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_graphicsView_windowIconChanged(const QIcon &icon);

    void setOverlay();

    void on_pushButton_4_released();

    void on_pushButton_5_released();

    void on_pushButton_3_released();

    void UDPoutput();

    void on_TransferPhoto_pressed();

    void on_TransferOverlay_pressed();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    //base
    QImage img;
    QPixmap pm;
    //overlay
    QImage img2;
    QPixmap pm2;
    //base+overlay
    QPixmap pm3;
    //Post brightness
    QPixmap pm4;
    //Post contrast
    QPixmap pm5;

    int brightnessOutput = 50;
    int contrastOutput = 50;
    QUdpSocket *socket;
    QTcpSocket *socketTcp;
    QString addr = "192.168.0.231";

};
#endif // MAINWINDOW_H
