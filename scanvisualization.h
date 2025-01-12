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
    float stepX;
    float stepZ;
    int zoom;
    std::vector<GLfloat> roomPoints;
    std::vector<GLint> roomIndices;
    std::vector<GLfloat> scanerPoints;
    std::vector<GLint> scanerIndices;
    QVector3D camTarget;
    std::vector<Scaner*> *scaners;
    void drawSmth(std::vector<GLfloat> &points,std::vector<GLint> &indices,QVector3D colour,QVector3D pos);
public:
    ScanVisualization(QWidget *pwgt,std::vector<Scaner*> *scanerVec,float roomL,float xStep,float roomW,float zStep,float roomH);
    void setZoom(int percent);
    void setCamYaw(float yaw);
    void setCamPitch(float pitch);
    void setPointHeight(int x,int z,float height);
    void setHeightAt(float x,float z,float h);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w,int h);
};

#endif // SCANVISUALIZATION_H
