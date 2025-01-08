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
    lastScanPoint=pos;
    myStatus=working;
    emit statusChanged(myStatus);
}

void Scaner::respondHandler(QJsonObject &jsonResponse)
{
    timeoutTimer->start();
    if(jsonResponse["type"].toString()=="Scan_result"){
        float r=jsonResponse["Range"].toInt();
        float yaw=jsonResponse["Yaw"].toDouble()/360.0f*2*M_PI;
        float pitch=jsonResponse["Pitch"].toDouble()/360.0f*2*M_PI;
        //Пусть направлен вдоль оси х из 0 h 0
        float x=myPos.y()*atan(yaw)*cos(pitch);
        float z=myPos.y()*atan(yaw)*sin(pitch);
        float h=myPos.y()-r*sin(yaw);
        lastScanPoint.setX(x);
        lastScanPoint.setY(h);
        lastScanPoint.setZ(z);
    }
}

QVector3D Scaner::getPos()
{
    return myPos;
}

QVector3D Scaner::getLastScanPoint()
{
    return lastScanPoint;
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
    //myStatus=timeout;
    emit statusChanged(myStatus);
}
