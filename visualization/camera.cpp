#include "camera.h"

Camera::Camera(QVector3D camTarget)
{
    yaw=pitch=distance=0;
    target=camTarget;
}

void Camera::setYaw(double newYaw)
{
    if(newYaw>=-90.0&&newYaw<=90.0)
        yaw=newYaw;
}

void Camera::setPitch(double newPitch)
{
    int del=newPitch/360;
    newPitch-=newPitch*del;
    pitch=newPitch;
}

void Camera::setDistance(double newDistance)
{
    if(newDistance>0)
        distance=newDistance;
}

QMatrix4x4 Camera::getViewMatrix()
{
    QMatrix4x4 viewMatrix;
    QVector3D position(distance*cos(yaw/360*2*M_PI)*sin(pitch/360*2*M_PI),
                             distance*sin(yaw/360*2*M_PI),
                             distance*cos(yaw/360*2*M_PI)*cos(pitch/360*2*M_PI));
    position+=target;
    QVector3D up(0.0f, 1.0f, 0.0f);
    viewMatrix.lookAt(position, target, up);
    return viewMatrix;
}
