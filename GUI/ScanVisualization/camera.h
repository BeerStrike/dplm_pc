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
    float yaw;
    float pitch;
    float distance;
public:
    Camera(QVector3D camTarget);
    void setYaw(float newYaw);
    void setPitch(float newPitch);
    void setDistance(float newDistance);
    QMatrix4x4 getViewMatrix();
};

#endif // CAMERA_H
