#ifndef SCANERVISUALIZATOR_H
#define SCANERVISUALIZATOR_H
#include "scancontroller.h"
#include "basevisualizator.h"
#define SCANER_LENGTH 0.06
#define SCANER_WIDTH 0.02
#define SCANER_HEIGHT 0.06

class ScanerVisualizator:public BaseVisualizator
{
    Q_OBJECT
private:
    QVector<GLdouble> points;
    QVector<GLuint> indices;
    QVector3D colour;
public:
    explicit ScanerVisualizator(ScanController *scController,QObject *parent = nullptr);
    void draw() override;
};

#endif // SCANERVISUALIZATOR_H
