#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QMatrix4x4>
#include <QObject>
class Camera: public QObject
{
    Q_OBJECT
private:
    QVector3D target;
    double yaw;
    double pitch;
    double distance;
public:
    Camera(QVector3D camTarget);
    void setYaw(double newYaw);
    void setPitch(double newPitch);
    void setDistance(double newDistance);
    QMatrix4x4 getViewMatrix();
};

#endif // CAMERA_H
