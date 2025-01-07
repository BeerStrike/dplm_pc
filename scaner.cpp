#include "scaner.h"

Scaner::Scaner(QHostAddress IPAdress)
{
    IP=IPAdress;
}

void Scaner::setPos(QVector3D pos)
{
    myPos=pos;
}

void Scaner::respondHandler(QJsonObject &jsonResponse)
{
    //обработка
}

QVector3D Scaner::getPos()
{
    return myPos;
}

Scaner::ScanerStatus Scaner::getStatus()
{
    return myStatus;
}

QHostAddress Scaner::getIP()
{
    return IP;
}
