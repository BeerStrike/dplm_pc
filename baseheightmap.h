#ifndef BASEHEIGHTMAP_H
#define BASEHEIGHTMAP_H

#include <QObject>

class BaseHeightMap : public QObject
{
    Q_OBJECT
public:
    explicit BaseHeightMap(QObject *parent = nullptr);
    virtual float getLength()=0;
    virtual float getWidth()=0;
    virtual float getStep()=0;
    virtual float getHeightAt(float x,float y)=0;
};

#endif // BASEHEIGHTMAP_H
