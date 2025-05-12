#ifndef AXISVISUALIZARTOR_H
#define AXISVISUALIZARTOR_H

#include "basevisualizator.h"
class AxisVisualizartor: public BaseVisualizator
{
    Q_OBJECT
private:
    QVector<GLdouble> points;
    QVector<GLuint> indices;
public:
    explicit AxisVisualizartor(ScanController *scController,QObject *parent = nullptr);
    void draw() override;
};

#endif // AXISVISUALIZARTOR_H
