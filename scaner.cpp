#include "scaner.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTcpSocket>
#include <iostream>
#define MY_TIMEOUT 3000
Scaner::Scaner(QHostAddress IPAdress,int udpPort)
{
    IP=IPAdress;
    port=udpPort;
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
        float h=myPos.y()-r*cos(yaw);
        lastScanPoint.setX(x);
        lastScanPoint.setY(h);
        lastScanPoint.setZ(z);
        emit recivePointHeight(x,z,h);
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

void Scaner::sendPointsToScan(std::vector<std::pair<float, float>> &pointsToScan)
{
    QTcpSocket *sct=new QTcpSocket();
    sct->connectToHost(IP,port);
        QJsonObject json;
    json.insert("Type","Angles_to_scan");
    QJsonArray anglesArray;
    for(int i=0;i<pointsToScan.size();i++){
        QJsonObject jsonPoint;
        float yaw=atan(sqrt(pow(pointsToScan.at(i).first,2)+pow(pointsToScan.at(i).second,2))/myPos.y())/M_PI*180;
        float pitch=atan(pointsToScan.at(i).first/pointsToScan.at(i).second)/M_PI*180;
        jsonPoint.insert("Yaw",yaw);
        jsonPoint.insert("Pitch",pitch);
        anglesArray.push_back(jsonPoint);
    }
    json.insert("Angles_array",anglesArray);
    sct->waitForConnected();
    QJsonDocument doc;
    doc.setObject(json);
    sct->write(doc.toJson());
    sct->waitForBytesWritten();
    sct->disconnectFromHost();
    delete sct;
}


void Scaner::on_timeout()
{
    //myStatus=timeout;
    emit statusChanged(myStatus);
}
