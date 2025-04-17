#ifndef AXISVISUALIZARTOR_H
#define AXISVISUALIZARTOR_H
#include <vector>
#include "visualization/basevisualizator.h"
class AxisVisualizartor: public BaseVisualizator
{
    Q_OBJECT
private:
    QVector<GLdouble> points;
    QVector<GLuint> indices;
public:
    explicit AxisVisualizartor(double xMax,double yMax,double zMax,QObject *parent = nullptr);
    void draw() override;
};

#endif // AXISVISUALIZARTOR_H
