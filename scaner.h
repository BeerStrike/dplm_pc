#ifndef SCANER_H
#define SCANER_H
#include <QObject>
#include <QHostAddress>
#include <QVector3D>
#include <QTimer>
#include <QJsonObject>
#include <QTcpSocket>
#include <QSettings>
#include "heightmap.h"
#include "room.h"

class Scaner:public QObject
{
    Q_OBJECT
public:
    enum ScanerStatus {unconfigured ,working,not_connected,connected};
    enum Direction {xdyd,xryd,xdyr,xryr};
    explicit Scaner(Room *rm,QHostAddress IPAdress,int tcpPsort,QObject *parent = nullptr);
    void setParams(QVector3D pos,Direction direction);
    QVector3D getPos();
    Direction getDirection();
    QVector3D getLastScanPoint();
    ScanerStatus getStatus();
    QHostAddress getIP();
    QString getName();
    BaseHeightMap *getHeightMap();
    ~Scaner();
signals:
    void statusChanged(Scaner *sc);
    void recivedPoint();
private:
    Room *rm;
    QString scanerName;
    QTcpSocket *sct;
    QByteArray rcvBuff;
    int brcntr;
    QVector3D myPos;
    QVector3D lastScanPoint;
    QHostAddress IP;
    HeightMap hm;
    int port;
    ScanerStatus myStatus;
    Direction dr;
    QTimer *timeoutTimer;
    void stateResponseHandler(QJsonObject &json);
    void stateHandler(QString stateName);
    void scanResultHandler(QJsonObject &json);
    void jsonProcessor(QJsonObject &json);
    void sendScanParameters();
private slots:
    void on_tcp_connected();
    void on_tcp_recive();
    void on_tcp_disconnected();
    void on_timeout();
};

#endif // SCANER_H
