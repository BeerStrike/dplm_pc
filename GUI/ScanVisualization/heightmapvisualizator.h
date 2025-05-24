#ifndef HEIGHTMAPVISUALIZATOR_H
#define HEIGHTMAPVISUALIZATOR_H

#include "basevisualizator.h"

class HeightMapVisualizator : public BaseVisualizator
{
    Q_OBJECT
private:
    void heigntMapToPoints(QVector<GLfloat> &points,QVector<GLuint> &indices);
public:
    explicit HeightMapVisualizator(ScanController *scController,QObject *parent = nullptr);
    void draw() override;
};

#endif // HEIGHTMAPVISUALIZATOR_H
