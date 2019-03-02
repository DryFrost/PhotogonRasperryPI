#ifndef CLIENT_H
#define CLIENT_H
#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
class Client: public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = 0);
   ~Client();
    void start(QHostAddress address, quint16 port);
    void SetImageData(QByteArray* pba_);
public slots:
    void startTransfer();
private:
    QTcpSocket client;
    QByteArray* pba;
};

#endif // CLIENT_H
