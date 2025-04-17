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
#include "listwidgetitemscaner.h"
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
        scaners.push_back(sc);
        ListWidgetItemScaner *isc=new ListWidgetItemScaner(sc);
        ui->scanerList->addItem(isc);
    }
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
}



void MainWindow::on_deleteScanerBtn_clicked()
{
    ListWidgetItemScaner *scitem=(ListWidgetItemScaner*)ui->scanerList->selectedItems().at(0);
    //ui->scanerList->re;
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
        ListWidgetItemScaner *isc=new ListWidgetItemScaner(sc);
        ui->scanerList->addItem(isc);
    }
}

