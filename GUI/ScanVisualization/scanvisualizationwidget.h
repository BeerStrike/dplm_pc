#ifndef SCANVISUALIZATIONWIDGET_H
#define SCANVISUALIZATIONWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLDebugLogger>
#include <vector>
#include <scaner.h>
#include "camera.h"
#include "scanervisualizator.h"
#include "axisvisualizartor.h"
#include "roomvisualizator.h"
#include "heightmapvisualizator.h"
#include "scancontroller.h"

class ScanVisualizationWidget : public QOpenGLWidget
{
    Q_OBJECT
private:
    QOpenGLShaderProgram shader;
    QOpenGLFunctions *f;
    QOpenGLExtraFunctions *ef;
    ScanerVisualizator scvs;
    AxisVisualizartor axvs;
    RoomVisualizator rmvs;
    HeightMapVisualizator hmvs;
    Camera *cam;
public:
    ScanVisualizationWidget(ScanController *sc,QWidget *pwgt);
    ~ScanVisualizationWidget();
    void setZoom(int percent);
    void setCamYaw(float yaw);
    void setCamPitch(float pitch);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w,int h);
};

#endif // SCANVISUALIZATIONWIDGET_H
