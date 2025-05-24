#ifndef SCANCONTROLLER_H
#define SCANCONTROLLER_H

#include <QObject>
#include <QVector>
#include "room.h"
#include "combinatedheightmap.h"
#include "scaner.h"
class ScanController : public QObject
{
    Q_OBJECT
private:
    Room *room;
    QVector<Scaner *> scaners;
    CombinatedHeightMap *heightMap;
private slots:
    void on_scanerGetData();
public:
    explicit ScanController(Room *rm,QObject *parent = nullptr);
    Room *getRoom();
    void setRoom(Room *rm);
    BaseHeightMap *getHeightMap();
    Scaner *addScaner(QHostAddress IPAdress,int tcpPort);
    Scaner *getScaner(int i);
    void removeScaner(Scaner *);
    int getScanersNum();
    void pauseScan();
    void continueScan();
    ~ScanController();
signals:
    void newData();
};

#endif // SCANCONTROLLER_H
