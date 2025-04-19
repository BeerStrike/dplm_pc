#ifndef HEIGHTMAPVISUALIZATOR_H
#define HEIGHTMAPVISUALIZATOR_H

#include "basevisualizator.h"
#include "baseheightmap.h"

class HeightMapVisualizator : public BaseVisualizator
{
    Q_OBJECT
private:
    BaseHeightMap *hm;
    void heigntMapToPoints(QVector<GLdouble> &points,QVector<GLuint> &indices);
public:
    explicit HeightMapVisualizator(BaseHeightMap * heightMap,QObject *parent = nullptr);
    void draw() override;
};

#endif // HEIGHTMAPVISUALIZATOR_H
