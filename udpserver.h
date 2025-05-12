#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(int pcPort,int scanersPort,QObject *parent = nullptr);
    ~UdpServer();
    void restart(int port);
    void searchScaners();
    void setScanersPort(int port);
signals:
    void findScaner(QHostAddress IP,int port);
private:
    QUdpSocket *udpSocket;
    int scPort;
private slots:
    void on_UDPRecive();

};

#endif // UDPSERVER_H
