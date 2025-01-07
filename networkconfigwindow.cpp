#include "networkconfigwindow.h"
#include "ui_networkconfigwindow.h"

NetworkConfigWindow::NetworkConfigWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NetworkConfigWindow)
{
    ui->setupUi(this);
}

NetworkConfigWindow::~NetworkConfigWindow()
{
    delete ui;
}

int NetworkConfigWindow::getPCPort()
{
    return ui->PCPortInput->text().toInt();
}

int NetworkConfigWindow::getScanerPort()
{
    return ui->scanerPortInput->text().toInt();
}

void NetworkConfigWindow::on_OKButton_clicked()
{
    if(getScanerPort()&&getPCPort())
        this->close();
}

