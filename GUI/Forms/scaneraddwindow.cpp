#include "scaneraddwindow.h"
#include "ui_scaneraddwindow.h"

ScanerAddWindow::ScanerAddWindow(ScanController *sc,QWidget *parent)
    : QDialog(parent),scCtrl(sc)
    , ui(new Ui::ScanerAddWindow)
{
    ui->setupUi(this);
    scaner=nullptr;
}

Scaner *ScanerAddWindow::getScaner()
{
    return scaner;
}

ScanerAddWindow::~ScanerAddWindow()
{
    delete ui;
}


void ScanerAddWindow::on_connectBtn_clicked()
{
    if(!ui->portInput->text().isNull()&&!ui->IPInput->text().isNull()){
        int port=ui->portInput->text().toInt();
        QHostAddress addr(ui->IPInput->text());
        scaner=scCtrl->addScaner(addr,port);
        this->close();
    }
}

