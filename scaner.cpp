#include "scaner.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>
#define MY_TIMEOUT 3000

Scaner::Scaner(Room *room,QHostAddress IPAdress,int udpPort,QObject *parent):
    QObject{parent},
    hm(room->getRoomLength(),
         room->getRoomWidth(),
         room->getStep())
{
    IP=IPAdress;
    port=udpPort;
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

void Scaner::setPos(QVector3D pos)
{
    myPos=pos;
    lastScanPoint=pos;
    rm->savePosOfScaner(scanerName,myPos);
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

QString Scaner::getName()
{
    if(scanerName!="")
        return scanerName;
    else
        return IP.toString();
}

void Scaner::sendScanParameters()
{
    QJsonObject json;
    json.insert("Type","Scan parameters");
    json.insert("Length",rm->getRoomLength());
    json.insert("Width",rm->getRoomWidth());
    json.insert("Height",rm->getRoomHeight());
    json.insert("Step",rm->getStep());
    QJsonDocument doc;
    doc.setObject(json);
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
        myPos=rm->getPosForScaner(name);
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
    double r=json["Range"].toDouble();
    double yaw=json["Yaw"].toDouble()/180.0f*M_PI;
    double pitch=json["Pitch"].toDouble()/180.0f*M_PI;
    //Пусть направлен вдоль оси х из 0 h
    double h=myPos.y()-r*cos(yaw);
    double x=r*sin(yaw)*cos(pitch);
    double z=r*sin(yaw)*sin(pitch);
    lastScanPoint.setX(x);
    lastScanPoint.setY(h);
    lastScanPoint.setZ(z);
    hm.setHeightAt(x,z,h);
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
