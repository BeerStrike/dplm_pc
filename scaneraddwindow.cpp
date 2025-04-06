#include "scaneraddwindow.h"
#include "ui_scaneraddwindow.h"

ScanerAddWindow::ScanerAddWindow(QUdpSocket *sct,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScanerAddWindow)
{
    ui->setupUi(this);
    udpSocket=sct;
}

ScanerAddWindow::~ScanerAddWindow()
{
    delete ui;
}

void ScanerAddWindow::on_connectBtn_clicked()
{
    char b[32];
    int port=ui->portInput->text().toInt();
    QHostAddress addr(ui->IPInput->text());
    udpSocket->writeDatagram(b,addr,port);
}

