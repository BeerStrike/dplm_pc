#include "scaner.h"
#define MY_TIMEOUT 3000
Scaner::Scaner(QHostAddress IPAdress)
{
    IP=IPAdress;
    myStatus=unconfigured;
    timeoutTimer=new QTimer(this);
    connect(timeoutTimer, &QTimer::timeout,this, &on_timeout);
    timeoutTimer->setInterval(MY_TIMEOUT);
    timeoutTimer->start();
}

void Scaner::setPos(QVector3D pos)
{
    myPos=pos;
    myStatus=working;
    emit statusChanged(myStatus);
}

void Scaner::respondHandler(QJsonObject &jsonResponse)
{
    timeoutTimer->start();
    //обработка
}

QVector3D Scaner::getPos()
{
    return myPos;
}

Scaner::ScanerStatus Scaner::getStatus()
{
    return myStatus;
}

QHostAddress Scaner::getIP()
{
    return IP;
}

void Scaner::on_timeout()
{
    myStatus=timeout;
    emit statusChanged(myStatus);
}
