#include "myudp.h"
#include "camera.h"

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
    }
    if(QString(buffer).compare("Capture")==0){
        c.capture();
    }
}

