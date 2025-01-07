#ifndef SCANVISUALIZATION_H
#define SCANVISUALIZATION_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <vector>
#include <scaner.h>

class ScanVisualization : public QOpenGLWidget
{
private:
    QOpenGLShaderProgram shader;
    QOpenGLFunctions *f;
    QOpenGLExtraFunctions *ef;
    int xPointsMax;
    int zPointsMax;
    float cameraYaw;
    float cameraPitch;
    int zoom;
    std::vector<GLfloat> points;
    std::vector<GLint> indices;
    QVector3D camTarget;
    std::vector<Scaner> *scaners;
public:
    ScanVisualization(QWidget *pwgt,float roomL,float xStep,float roomW,float zStep,float roomH);
    void setZoom(int percent);
    void setCamYaw(float yaw);
    void setCamPitch(float pitch);
    void setPointHeight(int x,int z,float height);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w,int h);
};

#endif // SCANVISUALIZATION_H
