#include "scanersetupwindow.h"
#include "ui_scanersetupwindow.h"

ScanerSetupWindow::ScanerSetupWindow(Scaner *scaner,QWidget *parent)
    : QDialog(parent),sc(scaner)
    , ui(new Ui::ScanerSetupWindow)
{
    ui->setupUi(this);
    QVector3D scpos=sc->getPos();
    ui->xCordInput->setText(QString::number(scpos.x()));
    ui->yCordInput->setText(QString::number(scpos.y()));
    ui->hCordInput->setText(QString::number(scpos.z()));
}

ScanerSetupWindow::~ScanerSetupWindow()
{
    delete ui;
}

void ScanerSetupWindow::on_OKButton_clicked()
{
    QVector3D pos;
    pos.setX(ui->xCordInput->text().toFloat());
    pos.setY(ui->yCordInput->text().toFloat());
    pos.setZ(ui->hCordInput->text().toFloat());

    Scaner::Direction dr;
    if(ui->xdydBtn->isChecked())
        dr=Scaner::xdyd;
    else if(ui->xrydBtn->isChecked())
        dr=Scaner::xdyr;
    else if(ui->xdyrBtn->isChecked())
        dr=Scaner::xryd;
    else
        dr=Scaner::xryr;
    sc->setParams(pos,dr);
    this->close();
}
