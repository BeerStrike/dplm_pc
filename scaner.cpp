#include "scaner.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>
#define MY_TIMEOUT 3000

Scaner::Scaner(QHostAddress IPAdress,int udpPort)
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
}

void Scaner::setPos(QVector3D pos)
{
    myPos=pos;
    lastScanPoint=pos;
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

void Scaner::sendScanParameters(float length,float width,float height,float step)
{
    QJsonObject json;
    json.insert("Type","Scan parameters");
    json.insert("Length",length);
    json.insert("Width",width);
    json.insert("Height",height);
    json.insert("Step",step);
    QJsonDocument doc;
    doc.setObject(json);
    sct->write(doc.toJson());
    sct->waitForBytesWritten();
}

Scaner::~Scaner()
{
    sct->disconnectFromHost();
    if(sct!=nullptr)
        delete sct;
    if(timeoutTimer!=nullptr)
        delete timeoutTimer;
}

void Scaner::on_tcp_connected()
{
    myStatus=connected;
    emit statusChanged(myStatus);
}

void Scaner::on_tcp_recive()
{
    QByteArray data =sct->readAll();
    char *d=data.data();
    QJsonParseError error;
    int st=0;
    while(st<data.size()){
        QByteArray subdata;
        int ed=st+1;
        int cntr=1;
        for(;ed<data.size();ed++){
            if(*(data.data()+ed)=='{')
                cntr++;
            if(*(data.data()+ed)=='}')
                cntr--;
            if(cntr==0)
                break;
        }
        subdata.resize(ed-st+1);
        memcpy(subdata.data(),data.data()+st,ed-st+1);
        st=ed+1;
        //TODO ???
        QJsonDocument jsonDoc = QJsonDocument::fromJson(subdata.data(),&error);
        if(error.error==QJsonParseError::NoError){
            QJsonObject  json = jsonDoc.object();
            if(json["Type"].toString()=="Scan result"){
                float r=json["Range"].toDouble();
                float yaw=json["Yaw"].toDouble()/180.0f*M_PI;
                float pitch=json["Pitch"].toDouble()/180.0f*M_PI;
                //Пусть направлен вдоль оси х из 0 h
                float h=myPos.y()-r*cos(yaw);
                float x=r*sin(yaw)*cos(pitch);
                float z=r*sin(yaw)*sin(pitch);
                lastScanPoint.setX(x);
                lastScanPoint.setY(h);
                lastScanPoint.setZ(z);
                emit recivePointHeight(x,z,h);
            }else if(json["Type"].toString()=="State response"){
                if(json["State"].toString()=="Wait for params")
                    myStatus=unconfigured;
                else if(json["State"].toString()=="Working")
                    myStatus=working;
                emit statusChanged(myStatus);
            }
        }
    }
}
void Scaner::on_tcp_disconnected()
{
    myStatus=not_connected;
    emit statusChanged(myStatus);
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
