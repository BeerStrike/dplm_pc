#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsForms/roomparametersinputform.h"
#include "settingsForms/networkconfigwindow.h"
#include "settingsForms/scaneruartsetupwindow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkDatagram>
#include <iostream>
#include "settingsForms/scanersetupwindow.h"
#include "scaneraddwindow.h"
#include <QTcpSocket>
#include <ctime>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings=new QSettings("settings.ini",QSettings::IniFormat);
    settings->beginGroup("Network_settings");
    udpsrv=new UdpServer(settings->value("PC_port").toInt(),this);
    connect(udpsrv,SIGNAL(findScaner(QHostAddress)),this,SLOT(on_findScaner(QHostAddress)));
    settings->endGroup();
    settings->beginGroup("Room_parameters");
    room=new Room("Room_1",settings->value("Length").toFloat(),
                  settings->value("Width").toFloat(),
                  settings->value("Height").toFloat(),
                    settings->value("Step").toFloat());
    scv=new ScanVisualizationWidget(room,&scaners,this);
    settings->endGroup();
    ui->verticalLayout->insertWidget(0,scv);
}

MainWindow::~MainWindow()
{
    for(unsigned int i=0;i<scaners.size();i++)
        delete scaners[i];
    if(room)
        delete room;
    delete scv;
    delete settings;
    delete udpsrv;
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
    NetworkConfigWindow *w=new NetworkConfigWindow(settings,this);
    w->exec();
    settings->beginGroup("Network_settings");
    udpsrv->restart(settings->value("PC_port").toInt());
    settings->endGroup();
    delete w;
}


void MainWindow::on_roonParametersConfigBtn_triggered()
{
    RoomParametersInputForm *w=new RoomParametersInputForm(settings,this);
    w->exec();
    delete w;
    if(scv)
        delete scv;
    settings->beginGroup("Room_parameters");
    scv=new ScanVisualizationWidget(room,&scaners,this);
    settings->endGroup();
    ui->verticalLayout->insertWidget(0,scv);
    scv->show();
}

void MainWindow::on_addScanerBtn_clicked()
{
    ScanerAddWindow *w=new ScanerAddWindow(this);
    w->exec();
    if(w->isSuccess()){
        Scaner *sc=new Scaner(room,w->getIP(),w->getPort());
        ui->scanerList->addItem(sc->getName());
    }
    delete w;
}


void MainWindow::on_setupScanerBtn_clicked()
{
    for(int i=0;i<scaners.size();i++){
        if(scaners.at(i)->getName()==(ui->scanerList->currentItem())->text()){
            ScanerSetupWindow* w=new ScanerSetupWindow(scaners.at(i),this);
            w->exec();
            delete w;
            break;
        }
    }
}

void MainWindow::on_deleteScanerBtn_clicked()
{
    int row=ui->scanerList->currentRow();
    int i=0;
    for(;i<scaners.size();i++)
        if(scaners[i]==sm.key(ui->scanerList->currentItem()))
            break;
    delete scaners.at(i);
    sm.remove(sm.key(ui->scanerList->currentItem()));
    delete ui->scanerList->takeItem(row);
    ui->scanerList->clearSelection();
    for(;i<scaners.size()-1;i++){
        scaners[i]=scaners[i+1];
    }
    scaners.resize(scaners.size()-1);
}


void MainWindow::on_findScanerBtn_clicked()
{
    settings->beginGroup("Network_settings");
    udpsrv->searchScaners(settings->value("Scaner_port").toInt());
    settings->endGroup();
}


void MainWindow::on_scanerSetupUART_triggered()
{
    ScanerUARTSetupWindow* w=new ScanerUARTSetupWindow(this);
    w->exec();
    delete w;
}

void MainWindow::on_findScaner(QHostAddress IP)
{
    unsigned int i=0;
    for(;i<scaners.size();i++)
        if(scaners[i]->getIP()==IP){
            break;
        }
    if(i==scaners.size()){
        settings->beginGroup("Network_settings");
        Scaner *sc=new Scaner(room,IP,settings->value("Scaner_port").toInt());
        settings->endGroup();
        scaners.push_back(sc);
        connect(sc,SIGNAL(statusChanged(Scaner *)),this,SLOT(on_scanerStatusChanged(Scaner *)));
        QListWidgetItem * iw=new QListWidgetItem(ui->scanerList);
        iw->setText(sc->getName()+": нет соединения");
        ui->scanerList->addItem(iw);
        sm.insert(sc,iw);
    }
}

void MainWindow::on_scanerStatusChanged(Scaner * sc)
{
    QString statusText;
    switch (sc->getStatus()){
        case Scaner::unconfigured:
            statusText="нет конфигурации";
            break;
        case Scaner::working:
            statusText="работает";
            break;
        case Scaner::not_connected:
            statusText="нет соединения";
            break;
        case Scaner::connected:
            statusText="соединено";
            break;

    }
    sm[sc]->setText(sc->getName()+": "+statusText);
}

