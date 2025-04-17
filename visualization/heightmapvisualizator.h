#ifndef HEIGHTMAPVISUALIZATOR_H
#define HEIGHTMAPVISUALIZATOR_H

#include "basevisualizator.h"
#include "heightmap.h"

class HeightMapVisualizator : public BaseVisualizator
{
    Q_OBJECT
private:
    HeightMap *hm;
    double stp;
    void heigntMapToPoints(QVector<GLdouble> &points,QVector<GLuint> &indices);
public:
    explicit HeightMapVisualizator(HeightMap * heightMap,double step,QObject *parent = nullptr);
    void draw() override;
};

#endif // HEIGHTMAPVISUALIZATOR_H
