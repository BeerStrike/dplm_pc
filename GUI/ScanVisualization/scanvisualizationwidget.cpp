#include "scanvisualizationwidget.h"
#include <QMatrix4x4>
#include <QVector3D>
#include <iostream>

ScanVisualizationWidget::ScanVisualizationWidget(ScanController *sc,QWidget *pwgt)
    :QOpenGLWidget(pwgt),
    scvs(sc),
    axvs(sc),
    rmvs(sc),
    hmvs(sc)
{
    QVector3D camTarget(sc->getRoom()->getRoomWidth()/2,sc->getRoom()->getRoomHeight()/2,sc->getRoom()->getRoomLength()/2);
    cam=new Camera(camTarget);
    cam->setDistance(4*sqrt(pow(sc->getRoom()->getRoomLength()/2,2)+pow(sc->getRoom()->getRoomHeight()/2,2)));
    cam->setYaw(45);

}

ScanVisualizationWidget::~ScanVisualizationWidget()
{
    delete cam;
}

void ScanVisualizationWidget::setZoom(int percent){
    double dist=4*(100.0f-percent)/100;
    cam->setDistance(dist);
    this->repaint();
}

void ScanVisualizationWidget::setCamYaw(float yaw)
{
    cam->setYaw(yaw);
    this->repaint();

}

void ScanVisualizationWidget::setCamPitch(float pitch)
{
    cam->setPitch(pitch);
    this->repaint();

}

void ScanVisualizationWidget::initializeGL()
{
    this->context()->format().setProfile(QSurfaceFormat::CoreProfile);
    this->context()->format().setOption(QSurfaceFormat::DebugContext);
    f=this->context()->functions();
    ef=this->context()->extraFunctions();
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex, "VertexShader.vert");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment, "FragmentShader.frag");
    shader.bindAttributeLocation("vertex_position",0);
    //shader.bindAttributeLocation("vertex_colour",1);
    shader.link();
    scvs.initalize(this->context(),&shader);
    axvs.initalize(this->context(),&shader);
    rmvs.initalize(this->context(),&shader);
    hmvs.initalize(this->context(),&shader);

}

void ScanVisualizationWidget::paintGL()
{
    f->glClearColor(1.0,1.0,1.0,0.0);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LESS);
    QMatrix4x4 viewMatrix=cam->getViewMatrix();
    QMatrix4x4 projectionMatrix;

    projectionMatrix.perspective(45.0f, ((float)this->width())/this->height(), 0.1f, 100.0f);

    f->glViewport(0, 0, this->size().width(), this->size().height());
    shader.bind();
    shader.setUniformValue("view", viewMatrix);
    shader.setUniformValue("projection", projectionMatrix);
    scvs.draw();
    axvs.draw();
    rmvs.draw();
    hmvs.draw();
}

void ScanVisualizationWidget::resizeGL(int w,int h)
{
    f->glViewport(0, 0, w, h);
}
