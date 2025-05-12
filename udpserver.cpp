#include "udpserver.h"
#include <QNetworkDatagram>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkInterface>

UdpServer::UdpServer(int pcPort,int scanersPort,QObject *parent)
    : QObject{parent},scPort(scanersPort)
{
    udpSocket=new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4,pcPort);
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

void UdpServer::searchScaners()
{
    QJsonObject json;
    json.insert("Type","Find request");
    QJsonDocument doc;
    doc.setObject(json);
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for(int i=0;i<list.size();i++){
        QList<QNetworkAddressEntry> entryList = list[i].addressEntries();
        for(int j=0;j<entryList.size();j++)
            udpSocket->writeDatagram(doc.toJson(),entryList[j].broadcast(),scPort);
    }
}

void UdpServer::setScanersPort(int port)
{
    scPort=port;
}

void UdpServer::on_UDPRecive()
{
    while(udpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram =udpSocket->receiveDatagram();
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(datagram.data(),&error);
        if(error.error==QJsonParseError::NoError){
            QJsonObject  json = jsonDoc.object();
            if(json["Type"].toString()=="Find response"){
                emit findScaner(datagram.senderAddress(),datagram.senderPort());
            }
        }else
            qDebug()<<error.errorString().toStdString();
    }
}
