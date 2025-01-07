#include "scanersetupwindow.h"
#include "ui_scanersetupwindow.h"

ScanerSetupWindow::ScanerSetupWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScanerSetupWindow)
{
    ui->setupUi(this);
}

ScanerSetupWindow::~ScanerSetupWindow()
{
    delete ui;
}
