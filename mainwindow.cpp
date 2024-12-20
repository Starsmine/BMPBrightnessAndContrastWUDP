#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QColor>
#include <QImage>
#include <QPainter>
#include <iostream>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QBuffer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Base
void MainWindow::on_pushButton_released()
{
    QString fileNamesBase = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("BMP Files (*.bmp)"));
    img = QImage(fileNamesBase);
    img.convertTo(QImage::Format_Grayscale8);
    pm = QPixmap::fromImage(img);
    ui->label_6->setPixmap(pm);
    setOverlay();
}

//overlays
void MainWindow::on_pushButton_2_released()
{
    QString fileNamesOverlay = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("BMP Files (*.bmp)"));
    img2 = QImage(fileNamesOverlay);
    img2.convertTo(QImage::Format_Grayscale8);
    img2 = img2.scaledToHeight(img.height());
    img2 = img2.scaledToWidth(img.width());
    pm2 = QPixmap::fromImage(img2);
    ui->label_7->setPixmap(pm2);
    setOverlay();
}

//brightness
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    QImage tmp = pm3.toImage();
    float shift = position;
    shift = shift * .01;
    QColor color;

    //scales brightness to slider position.
    for(int y = 0; y < tmp.height(); y++)
    {
        for(int x= 0; x < tmp.width(); x++)
        {
            color = tmp.pixelColor(x,y);
            int v = color.value();

            v = v * shift;
            if(v < 0)
                v = 0;
            if(v>255)
                v = 255;
            color.setHsv(color.hsvHue(),color.hsvSaturation(),v);


            // Apply the pixel color
            tmp.setPixelColor(x,y,color);
        }
    }
    pm4 = QPixmap::fromImage(tmp);
    on_horizontalSlider_2_sliderMoved(ui->horizontalSlider_2->sliderPosition());

    if (position <= 100){
        brightnessOutput = position / 2;
    }
    else{
        brightnessOutput = 50 + ((position - 100)/4);
    }

    if (brightnessOutput == 100)
        brightnessOutput = 99;

    UDPoutput();
}

//contrast
void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    QImage tmp = pm4.toImage();
    float intensity[255] = {0};
    float intensityProbability[255];
    float CumIntensityProbability[255];
    int newintensity[255];
    int pixlecount;
    int v;
    int vweighted;
    pixlecount = tmp.width() * tmp.height();

    QColor color;
    //build intesity array
    for(int y = 0; y < tmp.height(); y++)
    {
        for(int x= 0; x < tmp.width(); x++)
        {
            color = tmp.pixelColor(x,y);
            int v = color.value();

            intensity[v] += 1;
        }
    }

    //Build intensity probablity array
    for (int i = 0; i<256; i++) {
        intensityProbability[i] = intensity[i]/pixlecount;

    }

    //build cumulative intensity probability array
    CumIntensityProbability[0] = intensityProbability[0];
    for (int i = 1; i<256; i++) {
        CumIntensityProbability[i] = CumIntensityProbability[i-1]+intensityProbability[i];
    }

    //multiply the cumulative intensity probability array by the maximum value.
    for (int i = 0; i<256; i++)
    {
        newintensity[i] = CumIntensityProbability[i]*255;
        // std::cout << intensityProbability[i] << " ";
    }

    //go through the image pixel by pixel and map the old value to the new value. Slider position will scale the new value.
    for(int y = 0; y < tmp.height(); y++)
    {
        for(int x= 0; x < tmp.width(); x++)
        {
            color = tmp.pixelColor(x,y);
            v = newintensity[color.value()];
            vweighted = v*position + color.value()*(100-position);
            vweighted = vweighted/100;
            //std::cout << v << " ";
            color.setHsv(color.hsvHue(),color.hsvSaturation(),vweighted);

            tmp.setPixelColor(x,y,color);
        }
    }

    //print image to gui
    pm5 = QPixmap::fromImage(tmp);
    ui->label_8->setPixmap(pm5);

    //wrong formula for negative numbers
    if (position < 0)
        contrastOutput = (position*2.5) + 50;
    else
        contrastOutput = position/2 + 50;

    if (contrastOutput == 100)
        contrastOutput = 99;

    UDPoutput();
}


void MainWindow::on_graphicsView_windowIconChanged(const QIcon &icon)
{

}

// puts overlay image on top of base image
void MainWindow::setOverlay()
{
    pm3 = QPixmap::fromImage(img);
    QColor color;
    QImage tmp = pm3.toImage();
    for(int y = 0; y < img2.height(); y++)
    {
        for(int x= 0; x < img2.width(); x++)
        {
            color = img2.pixelColor(x,y);

            if(color.value() == 255){
                tmp.setPixelColor(x,y, img.pixelColor(x,y));
            }
            else{
                tmp.setPixelColor(x,y,color);
                std::cout << color.value() << " ";
            }
        }
    }
    pm3 = QPixmap::fromImage(tmp);
    MainWindow::on_pushButton_4_released();
    MainWindow::on_pushButton_5_released();
    ui->label_8->setPixmap(pm3);
}

//brightness reset
void MainWindow::on_pushButton_4_released()
{
    on_horizontalSlider_sliderMoved(100);
    ui->horizontalSlider->setSliderPosition(100);
    brightnessOutput = 50;
    UDPoutput();

}

//contrast reset
void MainWindow::on_pushButton_5_released()
{
    on_horizontalSlider_2_sliderMoved(0);
    ui->horizontalSlider_2->setSliderPosition(0);
    contrastOutput = 50;
    UDPoutput();
}


//Save output image
void MainWindow::on_pushButton_3_released()
{

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", ".", ".bmp");
    std::cout << fileName.toStdString();
    QImage imgout(fileName);
    imgout = pm5.toImage();
    imgout.convertTo(QImage::Format_Grayscale8);
    imgout.save(fileName);
}


void MainWindow::initSocket()
{
    socket = new QUdpSocket(this);
    //addr = new QHostAddress("192.168.0.73");
    socketTcp = new QTcpSocket(this);

}


void MainWindow::UDPoutput()
{
    std::string b = std::to_string(brightnessOutput);
    if (b.length() == 1){
        b = "0" + b;
    }

    std::string c = std::to_string(contrastOutput);
    if (c.length() == 1){
        c = "0" + c;
    }

    std::string alpha = b + c;
    QByteArray datagram = QByteArray::fromStdString(alpha);
    socket->writeDatagram(datagram, QHostAddress(addr), 80); //hardcoded address is an issue
}


void MainWindow::on_TransferPhoto_pressed()
{
      QByteArray datagram;
      QByteArray emptyDatagram;
      QBuffer buffer(&datagram);
      buffer.open(QIODevice::WriteOnly);
      img.save(&buffer, "BMP");
      int totalSize = datagram.size();
      int packetSize = 1020;
      quint16 numPackets = (totalSize + packetSize - 1) / packetSize;  // Calculate total packets needed
      int bytesSentTotal = 0;
      quint8 objectnumber = 0;

      for (quint16 i = 0; i < numPackets; ++i) {
          // Extract chunk
          _sleep(3);
          //    QThread::msleep(1)
          QByteArray serial;
          quint8 sa = i;
          quint8 sb = i>>8;
          serial.append(sb);
          serial.append(sa);
          serial.append(objectnumber);
          serial.append(objectnumber);
          QByteArray chunk = serial.append(datagram.mid(i * packetSize, packetSize));

          // Send chunk
          qint64 bytesSent = socket->writeDatagram(chunk, QHostAddress(addr), 80);

          // Check and log the result
          if (bytesSent == -1) {
              qDebug() << "Failed to send packet" << i << ":" << socket->errorString();
              break;
          } else {
              qDebug() << "Packet" << i << "sent with size" << bytesSent;
              bytesSentTotal += bytesSent;
          }
      }

      socket->writeDatagram(emptyDatagram, QHostAddress(addr), 80);
      // Final log to confirm if entire image data was sent
      if (bytesSentTotal == (totalSize + numPackets*4)) {
          qDebug() << "Entire image sent successfully. Total size:" << bytesSentTotal;
      } else {
          qDebug() << "Error: Not all data sent. Total sent:" << bytesSentTotal << "of" << totalSize;
      }
  }



void MainWindow::on_TransferOverlay_pressed()
{
    QByteArray datagram;
    QByteArray emptyDatagram;
    QBuffer buffer(&datagram);
    buffer.open(QIODevice::WriteOnly);
    img2.save(&buffer, "BMP");
    int totalSize = datagram.size();
    int packetSize = 1020;
    quint16 numPackets = (totalSize + packetSize - 1) / packetSize;  // Calculate total packets needed
    int bytesSentTotal = 0;

    for (quint16 i = 0; i < numPackets; ++i) {
        // Extract chunk
        _sleep(3);
        //    QThread::msleep(1)
        QByteArray serial;
        quint8 sa = i;
        quint8 sb = i>>8;
        serial.append(sb);
        serial.append(sa);
        serial.append(1);
        serial.append(1);
        QByteArray chunk = serial.append(datagram.mid(i * packetSize, packetSize));

        // Send chunk
        qint64 bytesSent = socket->writeDatagram(chunk, QHostAddress(addr), 80);

        // Check and log the result
        if (bytesSent == -1) {
            qDebug() << "Failed to send packet" << i << ":" << socket->errorString();
            break;
        } else {
            qDebug() << "Packet" << i << "sent with size" << bytesSent;
            bytesSentTotal += bytesSent;
        }
    }

    socket->writeDatagram(emptyDatagram, QHostAddress(addr), 80);
    // Final log to confirm if entire image data was sent
    if (bytesSentTotal == (totalSize + numPackets*4)) {
        qDebug() << "Entire image sent successfully. Total size:" << bytesSentTotal;
    } else {
        qDebug() << "Error: Not all data sent. Total sent:" << bytesSentTotal << "of" << totalSize;
    }
}

QByteArray &operator<<(QByteArray &l, quint8 r)
{
    l.append(r);
    return l;
}

QByteArray &operator<<(QByteArray &l, quint16 r)
{
    return l<<quint8(r>>8)<<quint8(r);
}



void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (img2.isNull())
        ui->checkBox->setCheckState(Qt::Unchecked);
    int i = int(ui->checkBox->checkState());
    QByteArray datagram;
    datagram.append(i);
    socket->writeDatagram(datagram, QHostAddress(addr), 80);
}

