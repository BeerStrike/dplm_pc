#include "room.h"
#include <cmath>

Room::Room(QString roomName,double room_length, double room_width, double room_height,double scan_step):
    hm(room_length,room_width,scan_step)
{
    length=room_length;
    width=room_width;
    height=room_height;
    step=scan_step;
    myName=roomName;
    settings=new QSettings(roomName+"_settings.ini",QSettings::IniFormat);
    /*
    settings->beginGroup("Room_parameters");
    length=settings->value("Length").toFloat();
    width=settings->value("Width").toFloat();
    height=settings->value("Height").toFloat();
    step=settings->value("Step").toFloat();
    settings->endGroup();
    */
}

double Room::getRoomWidth()
{
    return width;
}

double Room::getRoomHeight()
{
    return height;
}

double Room::getRoomLength()
{
    return length;
}

double Room::getStep()
{
    return step;
}

BaseHeightMap *Room::getHeightMap()
{
    return &hm;
}


QVector3D Room::getPosForScaner(QString name)
{
    QVector3D pos;
    if(settings->childGroups().contains(name+"_scaner")){
        settings->beginGroup(name+"_scaner");
        pos.setX(settings->value("X").toDouble());
        pos.setY(settings->value("Y").toDouble());
        pos.setZ(settings->value("H").toDouble());
        settings->endGroup();
    }
    return pos;
}

void Room::savePosOfScaner(QString name, QVector3D pos)
{
    if(!pos.isNull()){
        settings->beginGroup(name+"_scaner");
        settings->setValue("X",pos.x());
        settings->setValue("Y",pos.y());
        settings->setValue("H",pos.z());
        settings->endGroup();
    }
}

void Room::addHeightMap(BaseHeightMap *heightMap,QVector3D scanerPos)
{
    hm.addHeightMap(heightMap,scanerPos);
}

Room::~Room()
{
    settings->beginGroup("Room_parameters");
    settings->setValue("Width",width);
    settings->setValue("Length",length);
    settings->setValue("Height",height);
    settings->setValue("Step",step);
    settings->endGroup();
    delete settings;
}

