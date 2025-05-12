#include "roomparametersinputform.h"
#include "ui_roomparametersinputform.h"

RoomParametersInputForm::RoomParametersInputForm(QSettings *stngs,QWidget *parent)
    : QDialog(parent), ui(new Ui::RoomParametersInputForm),settings(stngs)
{
    ui->setupUi(this);
    settings->beginGroup("Last_config");
    QString roomFileName=settings->value("Room_file_name").toString();
    settings->endGroup();
    ui->roomFileNameInput->setText(roomFileName);
    room=new Room(roomFileName);
    ui->lengthInput->setText(QString::number(room->getRoomLength()));
    ui->widthInput->setText(QString::number(room->getRoomWidth()));
    ui->heightInput->setText(QString::number(room->getRoomHeight()));
    ui->scanStepInput->setText(QString::number(room->getScanStep()));
    ui->mapStepInput->setText(QString::number(room->getMapStep()));

}

Room *RoomParametersInputForm::getRoom()
{
    return room;
}

RoomParametersInputForm::~RoomParametersInputForm()
{
    delete ui;
}

void RoomParametersInputForm::on_saveBtn_clicked()
{
    bool ok=true;
    float w,l,h,scst,mpst;
    if(ok) w=ui->widthInput->text().toFloat(&ok);
    if(ok) l=ui->lengthInput->text().toFloat(&ok);
    if(ok) h=ui->heightInput->text().toFloat(&ok);
    if(ok) scst=ui->scanStepInput->text().toFloat(&ok);
    if(ok) mpst=ui->mapStepInput->text().toFloat(&ok);
    if(ok){
        room->changeRoomParams(l,w,h,scst,mpst);
        this->close();
    }
}


void RoomParametersInputForm::on_loadBtn_clicked()
{
    QString roomFileName=ui->roomFileNameInput->text();
    settings->beginGroup("Last_config");
    settings->setValue("Room_file_name",roomFileName);
    settings->endGroup();
    if(room)
        delete room;
    room=new Room(roomFileName);
    ui->lengthInput->setText(QString::number(room->getRoomLength()));
    ui->widthInput->setText(QString::number(room->getRoomWidth()));
    ui->heightInput->setText(QString::number(room->getRoomHeight()));
    ui->scanStepInput->setText(QString::number(room->getScanStep()));
    ui->mapStepInput->setText(QString::number(room->getMapStep()));

}

