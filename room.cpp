#include "room.h"
#include <cmath>

Room::Room(QString roomName,double room_length, double room_width, double room_height,double scan_step):
    hm(round(room_length/scan_step)+1,round(room_width/scan_step)+1)
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

HeightMap *Room::getHeightMap()
{
    return &hm;
}

double Room::getHeightAt(double x, double y)
{
    if(x>=0&&x<=length&&y>=0&&y<=width)
        return hm.getHeightAt(round(x/step),round(y/step));
    else
        return 0;
}

double Room::getHeightAtPoint(int x, int y)
{
    return hm.getHeightAt(x,y);
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

