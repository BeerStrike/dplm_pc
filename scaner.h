#ifndef SCANER_H
#define SCANER_H
#include <QObject>
#include <QHostAddress>
#include <QVector3D>
#include <QTimer>
#include <QJsonObject>

class Scaner:public QObject
{
    Q_OBJECT
public:
    enum ScanerStatus {unconfigured ,working,timeout };
    Scaner(QHostAddress IPAdress);
    void setPos(QVector3D pos);
    void respondHandler(QJsonObject &jsonResponse);
    QVector3D getPos();
    QVector3D getLastScanPoint();
    ScanerStatus getStatus();
    QHostAddress getIP();
    QTimer *timeoutTimer;
signals:
    void statusChanged(ScanerStatus newStatus);
private:
    QVector3D myPos;
    QVector3D lastScanPoint;
    QHostAddress IP;
    ScanerStatus myStatus;
private slots:
    void on_timeout();
};

#endif // SCANER_H
