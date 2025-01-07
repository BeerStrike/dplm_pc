#include "listwidgetitemscaner.h"


ListWidgetItemScaner::ListWidgetItemScaner(Scaner *scaner):    QListWidgetItem(),QObject()
{
    mysc=scaner;
    this->setText(mysc->getIP().toString());
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
        this->setText(mysc->getIP().toString()+": ожидает настройки");
        break;
    case Scaner::ScanerStatus::working:
        this->setText(mysc->getIP().toString()+": работает");
        break;
    case Scaner::ScanerStatus::timeout:
        this->setText(mysc->getIP().toString()+": таймаут");
        break;
    default:
        break;
    }
}
