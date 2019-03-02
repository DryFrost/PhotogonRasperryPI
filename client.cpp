#include "client.h"
#include <QDebug>
Client::Client(QObject* parent): QObject(parent)
{
    connect(&client, SIGNAL(connected()),this,SLOT(startTransfer()));
    pba = 0;
}
Client::~Client(){
    client.close();
}
void Client::start(QHostAddress address, quint16 port)
{
    //QHostAddress addr(address);
    client.connectToHost(address,port);
    qDebug() << "Trying to connect";

}
void Client::SetImageData(QByteArray *pba_){
    pba = pba_;
}

void Client::startTransfer(){
    qDebug() << pba->size();
    if(pba) client.write(*pba,pba->size());
}
