#include "scanersetupwindow.h"
#include "ui_scanersetupwindow.h"

ScanerSetupWindow::ScanerSetupWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScanerSetupWindow)
{
    ui->setupUi(this);
}

QVector3D ScanerSetupWindow::getScanerPos()
{
    QVector3D pos;
    pos.setX(ui->xCordInput->text().toFloat());
    pos.setY(ui->yCordInput->text().toFloat());
    pos.setZ(ui->zCordInput->text().toFloat());
    return pos;
}

ScanerSetupWindow::~ScanerSetupWindow()
{
    delete ui;
}

void ScanerSetupWindow::on_OKButton_clicked()
{
    this->close();
}

