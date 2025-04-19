#ifndef ROOM_H
#define ROOM_H
#include "combinatedheightmap.h"
#include <QVector3D>
#include <QSettings>

class Room
{
private:
    double height;
    double length;
    double width;
    double step;
    CombinatedHeightMap hm;
    QString myName;
    QSettings *settings;
public:
    Room(QString roomName,double room_length,double room_width,double room_height,double scan_step);
    double getRoomWidth();
    double getRoomHeight();
    double getRoomLength();
    double getStep();
    BaseHeightMap *getHeightMap();
    QVector3D getPosForScaner(QString name);
    void savePosOfScaner(QString name,QVector3D pos);
    void addHeightMap(BaseHeightMap *heightMap,QVector3D scanerPos);
    ~Room();
};

#endif // ROOM_H
