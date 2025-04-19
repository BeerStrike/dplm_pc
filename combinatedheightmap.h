#ifndef COMBINATEDHEIGHTMAP_H
#define COMBINATEDHEIGHTMAP_H

#include "baseheightmap.h"
#include "heightmap.h"
#include <QVector>
#include <QVector3D>

class CombinatedHeightMap : public BaseHeightMap
{
    Q_OBJECT
    QVector<BaseHeightMap *> hmv;
    QVector<QVector3D> scposv;
    float l;
    float w;
    float stp;
public:
    explicit CombinatedHeightMap(float length,float width,float step,QObject *parent = nullptr);
    int getXSize() override;
    int getYSize() override;
    float getLength() override;
    float getWidth() override;
    float getStep() override;
    float getHeightAt(float x,float y) override;
    float getHeightAtPoint(int x,int y) override;
    void addHeightMap(BaseHeightMap *hm,QVector3D scpos);
};

#endif // COMBINATEDHEIGHTMAP_H
