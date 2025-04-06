#ifndef LISTWIDGETITEMSCANER_H
#define LISTWIDGETITEMSCANER_H

#include <QObject>
#include <QListWidgetItem>
#include "scaner.h"
class ListWidgetItemScaner : public QObject,public QListWidgetItem
{
    Q_OBJECT
private:
    Scaner * mysc;
public:
    ListWidgetItemScaner(Scaner *scaner);
    Scaner *getScaner();
public slots:
    void on_statusChange(Scaner::ScanerStatus newStatus);
};

#endif // LISTWIDGETITEMSCANER_H
