#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include <QVector>
#include <QVector3D>
#include "baseheightmap.h"

class HeightMap:public BaseHeightMap
{
    Q_OBJECT
private:
    QVector<QVector3D> points;
    QVector<QVector<QVector<QVector3D>>> map;
    float l;
    float w;
    float stp;
public:
    HeightMap(float length,float width,float step,QObject *parent = nullptr);
    float getLength() override;
    float getWidth() override;
    float getStep() override;
    void addPoint(QVector3D point);
    float getHeightAt(float x,float y) override;
};

#endif // HEIGHTMAP_H
