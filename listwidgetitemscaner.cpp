#include "listwidgetitemscaner.h"


ListWidgetItemScaner::ListWidgetItemScaner(Scaner *scaner):    QListWidgetItem(),QObject()
{
    mysc=scaner;
    this->setText(mysc->getName()+": нет соединения");
    QObject::connect(mysc,&Scaner::statusChanged,this,&on_statusChange);
}

Scaner *ListWidgetItemScaner::getScaner()
{
    return mysc;
}

void ListWidgetItemScaner::on_statusChange(Scaner::ScanerStatus newStatus)
{
    switch (newStatus) {
    case Scaner::ScanerStatus::unconfigured:
        this->setText(mysc->getName()+": нет конфигурании");
        break;
    case Scaner::ScanerStatus::working:
        this->setText(mysc->getName()+": работает");
        break;
    case Scaner::ScanerStatus::not_connected:
        this->setText(mysc->getName()+": нет соединения");
        break;
    case Scaner::ScanerStatus::connected:
        this->setText(mysc->getName()+": соединено");
        break;
    default:
        break;
    }
}
