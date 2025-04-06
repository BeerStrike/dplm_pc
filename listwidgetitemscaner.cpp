#include "listwidgetitemscaner.h"


ListWidgetItemScaner::ListWidgetItemScaner(Scaner *scaner):    QListWidgetItem(),QObject()
{
    mysc=scaner;
    this->setText(mysc->getIP().toString()+": нет соединения");
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
        this->setText(mysc->getIP().toString()+": нет конфигурании");
        break;
    case Scaner::ScanerStatus::working:
        this->setText(mysc->getIP().toString()+": работает");
        break;
    case Scaner::ScanerStatus::not_connected:
        this->setText(mysc->getIP().toString()+": нет соединения");
        break;
    case Scaner::ScanerStatus::connected:
        this->setText(mysc->getIP().toString()+": соединено");
        break;
    default:
        break;
    }
}
