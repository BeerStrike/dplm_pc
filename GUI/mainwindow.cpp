#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GUI/Forms/scaneruartsetupwindow.h"
#include "GUI/Forms/roomparametersinputform.h"
#include "GUI/Forms/networkconfigwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings=new QSettings("settings.ini",QSettings::IniFormat);
    settings->beginGroup("Last_config");
    Room *room=new Room(settings->value("Room_file_name").toString());
    settings->endGroup();

    scCtrl=new ScanController(room);
    scv=new ScanVisualizatorWidget(scCtrl,this);
    settings->beginGroup("Network_settings");
    smng=new ScanersManadgerWidget(scCtrl,settings->value("PC_port").toInt(),settings->value("Scaner_port").toInt(),this);
    settings->endGroup();
    ui->horizontalLayout->addWidget(scv);
    ui->horizontalLayout->addWidget(smng);
    connect(scCtrl,SIGNAL(newData()),scv,SLOT(on_newScanData()));
}

MainWindow::~MainWindow()
{
    delete scCtrl;
    delete settings;
    delete ui;
}

void MainWindow::on_networkSettingsBtn_triggered()
{
    NetworkConfigWindow *w=new NetworkConfigWindow(settings,this);
    w->exec();
    settings->beginGroup("Network_settings");
    smng->setPorts(settings->value("PC_port").toInt(),settings->value("Scaner_port").toInt());
    settings->endGroup();
    delete w;
}


void MainWindow::on_roonParametersConfigBtn_triggered()
{
    RoomParametersInputForm *w=new RoomParametersInputForm(settings,this);
    w->exec();
    Room *room=w->getRoom();
    smng->clearList();
    scCtrl->setRoom(room);
    delete w;

}


void MainWindow::on_scanerSetupUART_triggered()
{
    ScanerUARTSetupWindow* w=new ScanerUARTSetupWindow(this);
    w->exec();
    delete w;
}
