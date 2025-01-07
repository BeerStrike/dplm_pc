#ifndef SCANER_H
#define SCANER_H
#include <QHostAddress>
#include <QVector3D>
class Scaner
{
private:
    QVector3D myPos;
    QHostAddress IP;
    enum ScanerStatus {unconfigured ,working };
    ScanerStatus myStatus;
public:
    Scaner(QHostAddress IPAdress);
    void setPos(QVector3D pos);
    void respondHandler(QJsonObject &jsonResponse);
    QVector3D getPos();
    ScanerStatus getStatus();
    QHostAddress getIP();
};

#endif // SCANER_H
