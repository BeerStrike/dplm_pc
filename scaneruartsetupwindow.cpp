#include "scaneruartsetupwindow.h"
#include "ui_scaneruartsetupwindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

ScanerUARTSetupWindow::ScanerUARTSetupWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScanerUARTSetupWindow)
{
    ui->setupUi(this);
    port=nullptr;
    QList<QSerialPortInfo> list =QSerialPortInfo::availablePorts();
    for(int i=0;i<list.size();i++)
        ui->COMPortComboBox->addItem(list[i].portName());
    port=new QSerialPort(this);
    port->setBaudRate(78800);
    port->setDataBits(QSerialPort::Data8);
    port->setStopBits(QSerialPort::OneStop);
    port->setParity(QSerialPort::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);
    connect(port,&QSerialPort::readyRead,this,&on_UART_recive);
    bracketCounter=0;
}

ScanerUARTSetupWindow::~ScanerUARTSetupWindow()
{
    if(port->isOpen())
        port->close();
   delete ui;
}

void ScanerUARTSetupWindow::on_connectBtn_clicked()
{
    if(port->isOpen())
        port->close();
    port->setPortName(ui->COMPortComboBox->currentText());
    if(port->open(QIODevice::ReadWrite)){
        QJsonObject json;
        json.insert("Type","Request settings");
        QJsonDocument doc;
        doc.setObject(json);
        port->write(doc.toJson());
    }else{
        QMessageBox messageBox(this);
        messageBox.critical(0,"Ошибка","Не удалось открыть порт");
        messageBox.setFixedSize(500,200);
    }
}


void ScanerUARTSetupWindow::on_saveBtn_clicked()
{
    if(port->isOpen()){
        QJsonObject json;
        json.insert("Type","Set settings");
        json.insert("Wi-fi SSID",ui->ssidInput->text());
        json.insert("Wi-fi password",ui->passInput->text());
        json.insert("Scaner name",ui->scanerNameInput->text());
        QJsonDocument doc;
        doc.setObject(json);
        port->write(doc.toJson());
    }else{
        QMessageBox messageBox(this);
        messageBox.critical(0,"Ошибка","Устройство не подключено");
        messageBox.setFixedSize(500,200);
    }
}

void ScanerUARTSetupWindow::on_UART_recive()
{
    QByteArray data=port->readAll();
    if(bracketCounter!=0||data[0]=='{'){
        for(int i=0;i<data.size();i++){
            jsonStr.push_back(data[i]);
            if(data[i]=='{')
                bracketCounter++;
            else if(data[i]=='}')
                bracketCounter--;
        }
        if(bracketCounter==0){
            QJsonParseError error;
            QJsonDocument jsonDoc=QJsonDocument::fromJson(jsonStr.data(),&error);
            if(error.error==QJsonParseError::NoError){
                QJsonObject json=jsonDoc.object();
                if(json["Type"].toString()=="Settings response"){
                    ui->ssidInput->setText(json["Wi-fi SSID"].toString());
                    ui->passInput->setText(json["Wi-fi password"].toString());
                    ui->scanerNameInput->setText(json["Scaner name"].toString());
                }
                jsonStr.clear();
            }
        }
    }
}

