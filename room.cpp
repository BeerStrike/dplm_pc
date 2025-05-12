#include "room.h"
#include <cmath>

Room::Room(QString roomFileName)
{
    myFileName=roomFileName;
    settings=new QSettings(roomFileName,QSettings::IniFormat);
    settings->beginGroup("Room_parameters");
    length=settings->value("Length").toFloat();
    width=settings->value("Width").toFloat();
    height=settings->value("Height").toFloat();
    scanStep=settings->value("Scan_step").toFloat();
    mapStep=settings->value("Map_step").toFloat();
    settings->endGroup();
}

float Room::getRoomWidth()
{
    return width;
}

float Room::getRoomHeight()
{
    return height;
}

float Room::getRoomLength()
{
    return length;
}


float Room::getScanStep()
{
    return scanStep;
}

float Room::getMapStep()
{
    return mapStep;
}

void Room::changeRoomParams(float l, float w, float h, float scStep, float mpStep)
{
    settings->beginGroup("Room_parameters");
    length=l;
    settings->setValue("Length",length);
    width=w;
    settings->setValue("Width",width);
    height=h;
    settings->setValue("Height",height);
    scanStep=scStep;
    settings->setValue("Scan_step",scanStep);
    mapStep=mpStep;
    settings->setValue("Map_step",mapStep);
    settings->endGroup();
}


QVector3D Room::getPosForScaner(QString name)
{
    QVector3D pos;
    if(settings->childGroups().contains(name+"_scaner")){
        settings->beginGroup(name+"_scaner");
        pos.setX(settings->value("X").toFloat());
        pos.setY(settings->value("Y").toFloat());
        pos.setZ(settings->value("H").toFloat());
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

Room::~Room()
{
    delete settings;
}

