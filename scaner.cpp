#include "scaner.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>
#define MY_TIMEOUT 3000

Scaner::Scaner(Room *room,QHostAddress IPAdress,int tcpPort,QObject *parent):
    QObject{parent},
    hm(room->getRoomLength(),
         room->getRoomWidth(),
         room->getMapStep())
{
    IP=IPAdress;
    port=tcpPort;
    myStatus=not_connected;
    sct=new QTcpSocket();
    sct->connectToHost(IP,port);
    connect(sct,&QTcpSocket::connected,this,&on_tcp_connected);
    connect(sct,&QTcpSocket::readyRead,this,&on_tcp_recive);
    connect(sct,&QTcpSocket::disconnected,this,&on_tcp_disconnected);

    timeoutTimer=new QTimer(this);
    timeoutTimer->setInterval(1000);
    connect(timeoutTimer, &QTimer::timeout,this, &on_timeout);
    timeoutTimer->start();
    scanerName="";

    brcntr=0;

    rm=room;
}

void Scaner::setParams(QVector3D pos,Direction direction)
{
    myPos=pos;
    dr=direction;
    lastScanPoint=pos;
    rm->savePosOfScaner(scanerName,myPos);
}


QVector3D Scaner::getPos()
{
    return myPos;
}

Scaner::Direction Scaner::getDirection()
{
    return dr;
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

QString Scaner::getName()
{
    if(scanerName!="")
        return scanerName;
    else
        return IP.toString();
}

BaseHeightMap *Scaner::getHeightMap()
{
    return &hm;
}

void Scaner::sendScanParameters()
{
    QJsonObject json;
    json.insert("Type","Scan parameters");
    json.insert("Room length",rm->getRoomLength());
    json.insert("Room width",rm->getRoomWidth());
    json.insert("Room height",rm->getRoomHeight());
    json.insert("Scan step",rm->getScanStep());
    json.insert("Scaner X",myPos.x());
    json.insert("Scaner Y",myPos.y());
    json.insert("Scaner H",myPos.z());
    switch(dr){
        case xdyd:
            json.insert("Scaner direction","xdyd");
            break;
        case xryd:
            json.insert("Scaner direction","xryd");
            break;
        case xdyr:
            json.insert("Scaner direction","xdyr");
            break;
        case xryr:
            json.insert("Scaner direction","xryr");
            break;
    }
    QJsonDocument doc;
    doc.setObject(json);
    QString j=doc.toJson();
    sct->write(doc.toJson());
    sct->waitForBytesWritten();
}

Scaner::~Scaner()
{
    sct->disconnectFromHost();
    if(sct)
        delete sct;
    if(timeoutTimer)
        delete timeoutTimer;
}

void Scaner::stateResponseHandler(QJsonObject &json)
{
    stateHandler(json["State"].toString());
    QString name=json["Scaner name"].toString();
    if(name.size()>0&&name!=scanerName){
        scanerName=name;
        //setPos(rm->getPosForScaner(name));
        emit statusChanged(this);
    }
}

void Scaner::stateHandler(QString stateName)
{
    if(stateName=="Wait for params"){
        if(myStatus!=unconfigured){
            myStatus=unconfigured;
            emit statusChanged(this);
        }
        if(!myPos.isNull())
            sendScanParameters();
    }
    else if(stateName=="Working")
        if(myStatus!=working){
            myStatus=working;
            emit statusChanged(this);
        }
}

void Scaner::scanResultHandler(QJsonObject &json)
{
    QVector3D point;
    point.setX(json["X"].toDouble());
    point.setY(json["Y"].toDouble());
    point.setZ(json["H"].toDouble());
    lastScanPoint.setX(point.x());
    lastScanPoint.setY(point.y());
    lastScanPoint.setZ(point.z());
    hm.addPoint(point);
    emit recivedPoint();
}

void Scaner::jsonProcessor(QJsonObject &json)
{
    if(json["Type"].toString()=="Scan result")
        scanResultHandler(json);
    else if(json["Type"].toString()=="State response"){
        stateResponseHandler(json);
    }
}

void Scaner::on_tcp_connected()
{
    myStatus=connected;
    emit statusChanged(this);
}

void Scaner::on_tcp_recive()
{
    QByteArray data =sct->readAll();
    for(int i=0;i<data.size();i++){
        if(data[i]=='{')
            brcntr++;
        if(brcntr>0)
            rcvBuff.push_back(data[i]);
        if(data[i]=='}')
            brcntr--;
        if(brcntr==0&&data[i]=='}'){
            QJsonParseError error;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(rcvBuff.data(),&error);
            qDebug()<<rcvBuff.data();
            if(error.error==QJsonParseError::NoError){
                QJsonObject json=jsonDoc.object();
                jsonProcessor(json);
            }
            rcvBuff.clear();
        }
    }
}

void Scaner::on_tcp_disconnected()
{
    myStatus=not_connected;
    emit statusChanged(this);
}

void Scaner::on_timeout()
{
    if(myStatus==not_connected){
        sct->connectToHost(IP,port);
    }else{
        QJsonObject json;
        json.insert("Type","State request");
        QJsonDocument doc;
        doc.setObject(json);
        sct->write(doc.toJson());
    }
}
