#ifndef ROOM_H
#define ROOM_H
#include <heightmap.h>
#include <QVector3D>
#include <QSettings>

class Room
{
private:
    double height;
    double length;
    double width;
    double step;
    HeightMap hm;
    QString myName;
    QSettings *settings;
public:
    Room(QString roomName,double room_length,double room_width,double room_height,double scan_step);
    double getRoomWidth();
    double getRoomHeight();
    double getRoomLength();
    double getStep();
    HeightMap *getHeightMap();
    double getHeightAt(double x, double y);
    double getHeightAtPoint(int x,int y);
    QVector3D getPosForScaner(QString name);
    void savePosOfScaner(QString name,QVector3D pos);
    ~Room();
};

#endif // ROOM_H
