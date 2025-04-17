#ifndef SCANERVISUALIZATOR_H
#define SCANERVISUALIZATOR_H
#include "scaner.h"
#include "visualization/basevisualizator.h"
#define SIZE_X 1.0
#define SIZE_Y 1.0
#define Scaner_HEIGHT 1.0

class ScanerVisualizator:public BaseVisualizator
{
    Q_OBJECT
private:
    QVector<GLdouble> points;
    QVector<GLuint> indices;
    QVector3D colour;
    std::vector<Scaner *> * sc;
public:
    explicit ScanerVisualizator(std::vector<Scaner *> * scaners,QObject *parent = nullptr);
    void draw() override;
};

#endif // SCANERVISUALIZATOR_H
