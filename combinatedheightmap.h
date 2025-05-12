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
    float getLength() override;
    float getWidth() override;
    float getStep() override;
    float getHeightAt(float x,float y) override;
    void addHeightMap(BaseHeightMap *hm,QVector3D scpos);
};

#endif // COMBINATEDHEIGHTMAP_H
