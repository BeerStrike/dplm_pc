#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "roomparametersinputform.h"
#include "networkconfigwindow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkDatagram>
#include <iostream>
#include "scanersetupwindow.h"
#include "listwidgetitemscaner.h"
#include "scaneraddwindow.h"
#include <QTcpSocket>
#include <QJsonArray>
#include <ctime>
#include <QNetworkInterface>

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
                                settings->value("Width").toFloat(),
                                settings->value("Height").toFloat(),
                                settings->value("Step").toFloat());
    settings->endGroup();
    ui->verticalLayout->insertWidget(0,scv);
}

MainWindow::~MainWindow()
{
    for(unsigned int i=0;i<scaners.size();i++)
        delete scaners[i];
    delete scv;
    delete settings;
    delete udpSocket;
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
    settings->setValue("Step",w->getStep());
    settings->endGroup();
    if(scv)
        delete scv;
    scv=new ScanVisualization(this,&scaners,w->getL(),w->getW(),w->getH(),w->getStep());
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
            unsigned int i=0;
            for(;i<scaners.size();i++)
                if(scaners[i]->getIP()==datagram.senderAddress()){
                    break;
                }
            if(i==scaners.size()&&json["type"].toString()=="Find_response"){
                settings->beginGroup("Network_settings");
                Scaner *sc=new Scaner(datagram.senderAddress(),settings->value("Scaner_port").toInt());
                settings->endGroup();
                connect(sc,&Scaner::recivePointHeight,this,&on_reciveScanResult);
                scaners.push_back(sc);
                ListWidgetItemScaner *isc=new ListWidgetItemScaner(sc);
                ui->scanerList->addItem(isc);
            }
        }else
                std::cerr<<error.errorString().toStdString();
    }
}


void MainWindow::on_reciveScanResult(float x, float z, float h)
{
    scv->setHeightAt(x,z,h);
    scv->repaint();
}


void MainWindow::on_addScanerBtn_clicked()
{
    ScanerAddWindow *w=new ScanerAddWindow(udpSocket,this);
    w->exec();
    delete w;
}


void MainWindow::on_setupScanerBtn_clicked()
{
    ListWidgetItemScaner *scitem=(ListWidgetItemScaner*)ui->scanerList->selectedItems().at(0);
    ScanerSetupWindow* w=new ScanerSetupWindow(this);
    w->exec();
    QVector3D pos=w->getScanerPos();
    scitem->getScaner()->setPos(pos);
    delete w;

    settings->beginGroup("Room_parameters");
    scitem->getScaner()->sendScanParameters(settings->value("Width").toFloat(),settings->value("Length").toFloat(),
                                            settings->value("Height").toFloat(),settings->value("Step").toFloat()
                                            );
    settings->endGroup();
}



void MainWindow::on_deleteScanerBtn_clicked()
{
    ListWidgetItemScaner *scitem=(ListWidgetItemScaner*)ui->scanerList->selectedItems().at(0);
    //ui->scanerList->re;
}


void MainWindow::on_findScanerBtn_clicked()
{
    char b[32];
    settings->beginGroup("Network_settings");
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for(int i=0;i<list.size();i++){
        QList<QNetworkAddressEntry> entryList = list[i].addressEntries();
        for(int j=0;j<entryList.size();j++)
            udpSocket->writeDatagram(b,entryList[j].broadcast(),settings->value("Scaner_port").toInt());
    }
    settings->endGroup();
}

