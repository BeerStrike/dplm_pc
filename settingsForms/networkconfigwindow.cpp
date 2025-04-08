#include "networkconfigwindow.h"
#include "ui_networkconfigwindow.h"

NetworkConfigWindow::NetworkConfigWindow(QSettings *stngs,QWidget *parent)
    : QDialog(parent),settings(stngs)
    , ui(new Ui::NetworkConfigWindow)
{
    ui->setupUi(this);
    settings->beginGroup("Network_settings");
    ui->PCPortInput->setText(settings->value("PC_port").toString());
    ui->scanerPortInput->setText(settings->value("Scaner_port").toString());
    settings->endGroup();
}

NetworkConfigWindow::~NetworkConfigWindow()
{
    delete ui;
}


void NetworkConfigWindow::on_OKButton_clicked()
{
    if(ui->PCPortInput->text().toInt()&&ui->scanerPortInput->text().toInt()){
        settings->beginGroup("Network_settings");
        settings->setValue("PC_port",ui->PCPortInput->text());
        settings->setValue("Scaner_port",ui->scanerPortInput->text());
        settings->endGroup();
        this->close();
    }
}

