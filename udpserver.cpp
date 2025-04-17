#include "udpserver.h"
#include <QNetworkDatagram>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkInterface>

UdpServer::UdpServer(int port,QObject *parent)
    : QObject{parent}
{
    udpSocket=new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4,port);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(on_UDPRecive()));
}

UdpServer::~UdpServer()
{
    if(udpSocket->isOpen())
        udpSocket->close();
    delete udpSocket;
}

void UdpServer::restart(int port)
{
    if(udpSocket)
        delete udpSocket;
    udpSocket=new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4,port);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(on_UDPRecive()));
}

void UdpServer::searchScaners(int port)
{
    char b[32];
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for(int i=0;i<list.size();i++){
        QList<QNetworkAddressEntry> entryList = list[i].addressEntries();
        for(int j=0;j<entryList.size();j++)
            udpSocket->writeDatagram(b,entryList[j].broadcast(),port);
    }
}

void UdpServer::on_UDPRecive()
{
    while(udpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram =udpSocket->receiveDatagram();
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(datagram.data(),&error);
        if(error.error==QJsonParseError::NoError){
            QJsonObject  json = jsonDoc.object();
            if(json["type"].toString()=="Find_response"){
                findScaner(datagram.senderAddress());
            }
        }else
            qDebug()<<error.errorString().toStdString();
    }
}
