#include "scancontroller.h"


void ScanController::on_scanerGetData()
{
    emit newData();
}

ScanController::ScanController(Room *rm, QObject *parent)
    : QObject{parent},room(rm)
{
    heightMap=new CombinatedHeightMap(room->getRoomLength(),room->getRoomWidth(),room->getMapStep(),this);
}

Room *ScanController::getRoom()
{
    return room;
}

void ScanController::setRoom(Room *rm)
{
    room=rm;
    //delete heightMap;
    heightMap=new CombinatedHeightMap(room->getRoomLength(),room->getRoomWidth(),room->getMapStep(),this);
    for(int i=0;i<scaners.size();i++)
        delete scaners[i];
    emit newData();
}

Scaner *ScanController::getScaner(int i)
{
    return scaners[i];
}

void ScanController::removeScaner(Scaner * scaner)
{
    int i=0;
    for(;i<scaners.size();i++)
        if(scaners[i]==scaner)
            break;
    delete scaner;
    for(;i<scaners.size()-1;i++){
        scaners[i]=scaners[i+1];
    }
    scaners.resize(scaners.size()-1);
}

BaseHeightMap *ScanController::getHeightMap()
{
    return heightMap;
}

Scaner *ScanController::addScaner(QHostAddress IPAdress, int tcpPort)
{
    Scaner *sc=new Scaner(room,IPAdress,tcpPort,this);
    scaners.push_back(sc);
    heightMap->addHeightMap(sc->getHeightMap(),sc->getPos());
    connect(sc,SIGNAL(recivedPoint()),this,SLOT(on_scanerGetData()));
    return sc;
}

int ScanController::getScanersNum()
{
    return scaners.size();
}

ScanController::~ScanController()
{
    delete heightMap;
    delete room;
    for(int i=0;i<scaners.size();i++)
        delete scaners[i];
}
