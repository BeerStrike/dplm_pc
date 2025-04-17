#include "scanvisualizationwidget.h"
#include <QMatrix4x4>
#include <QVector3D>
#include <iostream>

ScanVisualizationWidget::ScanVisualizationWidget(Room  *room,std::vector<Scaner*> *scanerVec,QWidget *pwgt)
    :QOpenGLWidget(pwgt),
    scvs(scanerVec),
    axvs(room->getRoomLength()*2,room->getRoomWidth()*2,room->getRoomHeight()*2),
    rmvs(room),
    hmvs(room->getHeightMap(),room->getStep())
{
    rm=room;
    QVector3D camTarget(room->getRoomLength()/2,room->getRoomHeight()/2,room->getRoomWidth()/2);
    cam=new Camera(camTarget);
    cam->setDistance(4*sqrt(pow(room->getRoomLength()/2,2)+pow(room->getRoomHeight()/2,2)));
    cam->setYaw(45);

}

ScanVisualizationWidget::~ScanVisualizationWidget()
{
    delete cam;
}

void ScanVisualizationWidget::setZoom(int percent){
    double dist=8*sqrt(pow(rm->getRoomLength()/2,2)+pow(rm->getRoomHeight()/2,2))*(100-percent)/100;
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
