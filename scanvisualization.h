#ifndef SCANVISUALIZATION_H
#define SCANVISUALIZATION_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLDebugLogger>
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
    float step;
    int zoom;
    std::vector<GLfloat> roomPoints;
    std::vector<GLint> roomIndices;
    std::vector<GLfloat> axisPoints;
    std::vector<GLint> axisIndices;
    std::vector<GLfloat> scanerPoints;
    std::vector<GLint> scanerIndices;
    QVector3D camTarget;
    std::vector<Scaner*> *scaners;
    QOpenGLDebugLogger *loger;
    void drawSmth(std::vector<GLfloat> &points,std::vector<GLint> &indices,QVector3D colour,QVector3D pos);
public:
    ScanVisualization(QWidget *pwgt,std::vector<Scaner*> *scanerVec,float roomL,float roomW,float roomH,float dotStep);
    void setZoom(int percent);
    void setCamYaw(float yaw);
    void setCamPitch(float pitch);
    void setPointHeight(int x,int z,float height);
    void setHeightAt(float x,float z,float h);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w,int h);
private slots:
    void on_logRecive(const QOpenGLDebugMessage &debugMessage);
};

#endif // SCANVISUALIZATION_H
