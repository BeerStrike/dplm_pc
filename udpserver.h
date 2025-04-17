#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(int port,QObject *parent = nullptr);
    ~UdpServer();
    void restart(int port);
    void searchScaners(int port);
private:
    QUdpSocket *udpSocket;
private slots:
    void on_UDPRecive();
signals:
    void findScaner(QHostAddress IP);
};

#endif // UDPSERVER_H
