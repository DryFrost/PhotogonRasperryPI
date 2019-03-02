#include "myudp.h"
#include "camera.h"
#include <opencv2/opencv.hpp>
#include <QByteArray>
#include <QFile>
#include <QImage>
#include <qpainter.h>
#include <QDebug>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <raspicam/raspicam_still_cv.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <string.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
using namespace cv;
raspicam::RaspiCam_Still_Cv CameraD;
MyUDP::MyUDP(QObject *parent) :
 QObject(parent)
{
 qDebug() << "Binding UDP Socket";
 socket = new QUdpSocket(this);
 socket->bind(QHostAddress::Any, 5000); //bind to 5000
 connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
 QByteArray data;
 data.append("PI");
 socket->writeDatagram(data, QHostAddress::Broadcast, 5000); //broadcast from port 5000
}

void MyUDP::readyRead(){
    Camera c;
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    //var to store headers from udp
    QHostAddress sender;
    quint16 sender_port;
    socket->readDatagram(buffer.data(),buffer.size(), &sender, &sender_port);
    qDebug() << "Message from " << sender << " port " << sender_port;
    qDebug() << "Msg: " << buffer;
    if(QString(buffer).compare("Request")==0){
        QByteArray data;
        data.append("PI");
        socket->writeDatagram(data, sender, 5000); //reply back with a PI
        //c.capture();
        QPixmap img("image.png");
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        QImage myImage;
        myImage.save(&buffer,"PNG");
        if(!myImage.isNull()){
            client.SetImageData(&ba);
            client.start(sender,8888);
        }
    }
    if(QString(buffer).compare("Capture")==0){
        //cv::Mat ImageBuffer;
        //ImageBuffer = c.capture();
        //QByteArray ImgByteI((char*)(ImageBuffer.data),15116544);
        //socket->writeDatagram(ImgByteI,sender,5000);
       // Mat toSend = Mat(1944,2592,CV_8UC3,ImgByteI.data());
       // imwrite("/home/pi/Desktop/sending.png",toSend);
        //c.capture();

        //Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
        CameraD.set(cv::CAP_PROP_FRAME_WIDTH,2592);
        CameraD.set(cv::CAP_PROP_FRAME_HEIGHT,1944);
        CameraD.open();
        cv::Mat imga;
        sleep(1);


            CameraD.grab();



                /* get a frame from camera */
                    CameraD.retrieve(imga);
                    //imwrite("/home/pi/Desktop/test1.jpg",img);

                    //resize(img,img,size);

                    //imgSize = img.total()*img.elemSiz
                    CameraD.release();

    //}
        //Mat3b meanImage = getMean(images);
                    qDebug() << "Right FUCKING HERE";
        imwrite("/home/pi/Desktop/test1.png",imga);
        qDebug() << "Right FUCKING HERE";
        QImage myImage;
        myImage.load("/home/pi/Desktop/test1.png");
        //QPixmap img("/home/pi/Desktop/test1.png");
        qDebug() << "Right FUCKING HERE";
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);

        myImage.save(&buffer,"PNG");
        if(!myImage.isNull()){
            client.SetImageData(&ba);
            client.start(sender,8888);
        }
    }
}

