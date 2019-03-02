#ifndef MYUDP_H
#define MYUDP_H
#include <QObject>
#include <QUdpSocket>
#include <QDebug>
#include <QNetworkInterface>
#include <client.h>

class MyUDP : public QObject
{
 Q_OBJECT
public:
 explicit MyUDP(QObject *parent = 0);
public slots:
 void readyRead();

private:
 QUdpSocket *socket;
 QByteArray ba;
 Client client;
};

#endif // MYUDP_H
