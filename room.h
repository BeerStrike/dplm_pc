#ifndef ROOM_H
#define ROOM_H
#include <QVector3D>
#include <QSettings>
#include <QObject>

class Room :public QObject
{
    Q_OBJECT
private:
    float height;
    float length;
    float width;
    float scanStep;
    float mapStep;
    QString myFileName;
    QSettings *settings;
public:
    Room(QString roomFileName);
    float getRoomWidth();
    float getRoomHeight();
    float getRoomLength();
    float getScanStep();
    float getMapStep();
    void changeRoomParams(float l,float w,float h,float scStep,float mpStep);
    QVector3D getPosForScaner(QString name);
    void savePosOfScaner(QString name,QVector3D pos);
    ~Room();
};

#endif // ROOM_H
