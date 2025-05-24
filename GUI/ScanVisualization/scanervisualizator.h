#ifndef SCANERVISUALIZATOR_H
#define SCANERVISUALIZATOR_H
#include "scancontroller.h"
#include "basevisualizator.h"
#define SCANER_LENGTH 0.06f
#define SCANER_WIDTH 0.02f
#define SCANER_HEIGHT 0.06f

class ScanerVisualizator:public BaseVisualizator
{
    Q_OBJECT
private:
    void genergatePointsAndIndices(QVector<GLfloat> &points,QVector<GLuint> &indices);
public:
    explicit ScanerVisualizator(ScanController *scController,QObject *parent = nullptr);
    void draw() override;
};

#endif // SCANERVISUALIZATOR_H
