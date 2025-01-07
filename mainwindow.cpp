#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "roomparametersinputform.h"
#include "networkconfigwindow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkDatagram>
#include <iostream>
#include "scanersetupwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings=new QSettings("settings.ini",QSettings::IniFormat);
    settings->beginGroup("Network_settings");
    udpSocket=new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4,settings->value("PC_port").toInt());
    connect(udpSocket, &QUdpSocket::readyRead,this, &on_UDPRecive);
    settings->endGroup();

    settings->beginGroup("Room_parameters");
    scv=new ScanVisualization(this,&scaners,
                                settings->value("Length").toFloat(),
                                settings->value("X_step").toFloat(),
                                settings->value("Width").toFloat(),
                                settings->value("Z_step").toFloat(),
                                settings->value("Height").toFloat());
    settings->endGroup();
    ui->verticalLayout->insertWidget(0,scv);

    scanerFindTimer=new QTimer(this);
    connect(scanerFindTimer, &QTimer::timeout,this, &on_scanerFindTimerTimeout);
    scanerFindTimer->setInterval(1000);
    scanerFindTimer->start();
}

MainWindow::~MainWindow()
{
    for(int i=0;i<scaners.size();i++)
        delete scaners[i];
    delete scv;
    delete settings;
    delete udpSocket;
    delete scanerFindTimer;
    delete ui;
}


void MainWindow::on_zoomSlider_sliderMoved(int position)
{
    scv->setZoom(position);
}


void MainWindow::on_yawSlider_sliderMoved(int position)
{
    scv->setCamYaw((position-50)/50.0*90.0);
}


void MainWindow::on_pitchSlider_sliderMoved(int position)
{
    scv->setCamPitch((position-50)/50.0*180.0);
}


void MainWindow::on_networkSettingsBtn_triggered()
{
    NetworkConfigWindow *w=new NetworkConfigWindow(this);
    w->exec();
    settings->beginGroup("Network_settings");
    settings->setValue("PC_port",w->getPCPort());
    settings->setValue("Scaner_port",w->getScanerPort());
    settings->endGroup();
    if(udpSocket)
        delete udpSocket;
    udpSocket=new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4,settings->value("PC_port").toInt());
    connect(udpSocket, &QUdpSocket::readyRead,this, &on_UDPRecive);
    delete w;
}


void MainWindow::on_roonParametersConfigBtn_triggered()
{
    RoomParametersInputForm *w=new RoomParametersInputForm(this);
    w->exec();
    settings->beginGroup("Room_parameters");
    settings->setValue("Width",w->getW());
    settings->setValue("Length",w->getL());
    settings->setValue("Height",w->getH());
    settings->setValue("X_step",w->getXStep());
    settings->setValue("Z_step",w->getZStep());
    settings->endGroup();
    if(scv)
        delete scv;
    scv=new ScanVisualization(this,&scaners,w->getL(),w->getXStep(),w->getW(),w->getZStep(),w->getH());
    delete w;
    ui->verticalLayout->insertWidget(0,scv);
    scv->show();
}

void MainWindow::on_UDPRecive()
{
    while(udpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram =udpSocket->receiveDatagram();
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(datagram.data(),&error);
        if(error.error==QJsonParseError::NoError){
            QJsonObject  json = jsonDoc.object();
            if(json["type"].toString()=="find_response"){
                unsigned int i=0;
                for(;i<scaners.size();i++)
                    if(scaners[i]->getIP()==datagram.senderAddress()){
                        scaners[i]->respondHandler(json);
                        break;
                    }
                if(i==scaners.size()){
                    ui->scanerList->addItem(datagram.senderAddress().toString());
                    Scaner *sc=new Scaner(datagram.senderAddress());
                    scaners.push_back(sc);
                }
            }
        }
    }
}

void MainWindow::on_scanerFindTimerTimeout()
{
    char b[32];
    settings->beginGroup("Network_settings");
    udpSocket->writeDatagram(b,QHostAddress::Broadcast,settings->value("Scaner_port").toInt());
    settings->endGroup();
}

void MainWindow::on_scanerList_itemClicked(QListWidgetItem *item)
{
    item->setSelected(false);
    QHostAddress IP(item->text());
    for(unsigned int i=0;i<scaners.size();i++)
        if(IP==scaners[i]->getIP()){
            ScanerSetupWindow* w=new ScanerSetupWindow(this);
            w->exec();
            QVector3D pos=w->getScanerPos();
            scaners[i]->setPos(pos);
            delete w;
        }
}

