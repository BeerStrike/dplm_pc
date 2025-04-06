#ifndef SCANER_H
#define SCANER_H
#include <QObject>
#include <QHostAddress>
#include <QVector3D>
#include <QTimer>
#include <QJsonObject>
#include <QTcpSocket>

class Scaner:public QObject
{
    Q_OBJECT
public:
    enum ScanerStatus {unconfigured ,working,not_connected,connected};
    Scaner(QHostAddress IPAdress,int udpPort);
    void setPos(QVector3D pos);
    QVector3D getPos();
    QVector3D getLastScanPoint();
    ScanerStatus getStatus();
    QHostAddress getIP();
    void sendScanParameters(float length,float width,float height,float step);
    ~Scaner();
signals:
    void statusChanged(ScanerStatus newStatus);
    void recivePointHeight(float x, float z, float h);
private:
    QTcpSocket *sct;
    QVector3D myPos;
    QVector3D lastScanPoint;
    QHostAddress IP;
    int port;
    ScanerStatus myStatus;
    QTimer *timeoutTimer;
private slots:
    void on_tcp_connected();
    void on_tcp_recive();
    void on_tcp_disconnected();
    void on_timeout();
};

#endif // SCANER_H
