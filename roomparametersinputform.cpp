#include "roomparametersinputform.h"
#include "ui_roomparametersinputform.h"

RoomParametersInputForm::RoomParametersInputForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RoomParametersInputForm)
{
    ui->setupUi(this);
}

float RoomParametersInputForm::getW()
{
    return ui->widthInput->text().toFloat();
}

float RoomParametersInputForm::getL()
{
    return ui->lengthInput->text().toFloat();

}

float RoomParametersInputForm::getH()
{
    return ui->heightInput->text().toFloat();
}

float RoomParametersInputForm::getStep()
{
    return ui->stepInput->text().toFloat();
}

RoomParametersInputForm::~RoomParametersInputForm()
{
    delete ui;
}

void RoomParametersInputForm::on_OKBtn_clicked()
{
    if(getW()!=0&&getL()!=0&&getH()!=0&&getStep()!=0)
        this->close();
}

