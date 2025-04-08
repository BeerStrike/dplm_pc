#include "scaneraddwindow.h"
#include "ui_scaneraddwindow.h"

ScanerAddWindow::ScanerAddWindow(QUdpSocket *sct,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScanerAddWindow)
{
    ui->setupUi(this);
    success=false;
}

ScanerAddWindow::~ScanerAddWindow()
{
    delete ui;
}

QHostAddress ScanerAddWindow::getIP()
{
    return ip;
}

int ScanerAddWindow::getPort()
{
    return port;
}

bool ScanerAddWindow::isSuccess()
{
    return success;
}

void ScanerAddWindow::on_connectBtn_clicked()
{
    if(!ui->portInput->text().isNull()&&!ui->IPInput->text().isNull()){
        port=ui->portInput->text().toInt();
        QHostAddress addr(ui->IPInput->text());
        ip=addr;
        success=true;
        this->close();
    }
}

