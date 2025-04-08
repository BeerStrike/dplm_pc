#include "roomparametersinputform.h"
#include "ui_roomparametersinputform.h"

RoomParametersInputForm::RoomParametersInputForm(QSettings *stngs,QWidget *parent)
    : QDialog(parent),settings(stngs)
    , ui(new Ui::RoomParametersInputForm)
{
    ui->setupUi(this);
    settings->beginGroup("Room_parameters");
    ui->widthInput->setText(QString::number(settings->value("Width").toFloat()));
    ui->lengthInput->setText(QString::number(settings->value("Length").toFloat()));
    ui->heightInput->setText(QString::number(settings->value("Height").toFloat()));
    ui->stepInput->setText(QString::number(settings->value("Step").toFloat()));
    settings->endGroup();
}

RoomParametersInputForm::~RoomParametersInputForm()
{
    delete ui;
}

void RoomParametersInputForm::on_OKBtn_clicked()
{
    bool ok=true;
    float w,l,h,st;
    if(ok) w=ui->widthInput->text().toFloat(&ok);
    if(ok) l=ui->lengthInput->text().toFloat(&ok);
    if(ok) h=ui->heightInput->text().toFloat(&ok);
    if(ok) st=ui->stepInput->text().toFloat(&ok);
    if(ok){
        settings->beginGroup("Room_parameters");
        settings->setValue("Width",w);
        settings->setValue("Length",l);
        settings->setValue("Height",h);
        settings->setValue("Step",st);
        settings->endGroup();
        this->close();
    }
}

