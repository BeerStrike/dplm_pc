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
    explicit Scaner(Room *rm,QHostAddress IPAdress,int port,QObject *parent = nullptr);
    void setPos(QVector3D pos);
    QVector3D getPos();
    QVector3D getLastScanPoint();
    ScanerStatus getStatus();
    QHostAddress getIP();
    QString getName();
    ~Scaner();
signals:
    void statusChanged(Scaner *sc);
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
