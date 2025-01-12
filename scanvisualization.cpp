#include "scanvisualization.h"
#include <QMatrix4x4>
#include <QVector3D>
#include <iostream>

void ScanVisualization::drawSmth(std::vector<GLfloat> &points, std::vector<GLint> &indices, QVector3D colour,QVector3D pos)
{
    QMatrix4x4 modelMatrix;
    modelMatrix.scale(1.0f);
    modelMatrix.translate(pos);
    shader.setUniformValue("model", modelMatrix);
    shader.setUniformValue("colour",colour);
    GLuint coords_vbo = 0;
    f->glGenBuffers(1, &coords_vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
    ef->glBufferData(GL_ARRAY_BUFFER, points.size() * 3*sizeof(GLfloat), &(points[0]), GL_STATIC_DRAW);
    GLuint elementbuffer;
    f->glGenBuffers(1, &elementbuffer);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    ef->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &(indices[0]), GL_STATIC_DRAW);
    GLuint vao = 0;
    ef->glGenVertexArrays(1, &vao);
    ef->glBindVertexArray(vao);
    f->glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    ef->glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
    ef->glDeleteVertexArrays(1, &vao);
    f->glDeleteBuffers(1, &coords_vbo);
    f->glDeleteBuffers(1, &elementbuffer);
}

ScanVisualization::ScanVisualization(QWidget *pwgt,std::vector<Scaner*> *scanerVec,float roomL,float xStep,float roomW,float zStep,float roomH):QOpenGLWidget(pwgt){
    xPointsMax=roomL/xStep;
    zPointsMax=roomW/zStep;
    stepX=xStep;
    stepZ=zStep;
    scaners=scanerVec;
    zoom=5;
    cameraYaw=45.0f;
    cameraPitch=0;
    roomPoints={
        0,0,0,
        roomL,0,0,
        0,0,roomW,
        roomL,0,roomW,

        0,roomH,0,
        roomL,roomH,0,
        0,roomH,roomW,
        roomL,roomH,roomW,
    };
    for(int i=0;i<=xPointsMax;i++)
        for(int j=0;j<=zPointsMax;j++){
            roomPoints.push_back(i*(roomL/xPointsMax));
            roomPoints.push_back(0);
            roomPoints.push_back(j*(roomW/zPointsMax));
        }
    roomIndices= {  0,1,
        0,2,
        3,1,
        3,2,

        4,5,
        4,6,
        7,5,
        7,6,

        0,4,
        1,5,
        2,6,
        3,7
    };
    for(int j=0;j<xPointsMax;j++){
        for(int i=0;i<zPointsMax;i++){
                roomIndices.push_back(8+i+j*(xPointsMax+1));
                roomIndices.push_back(8+i+(xPointsMax+1)+j*(xPointsMax+1));
                roomIndices.push_back(8+i+j*(xPointsMax+1));
                roomIndices.push_back(8+i+1+j*(xPointsMax+1));

            }
    }
    scanerPoints={
        -0.5,-0.5,-0.5,
        0.5,-0.5,-0.5,
        -0.5,-0.5,0.5,
        0.5,-0.5,0.5,

        -0.5,0.5,-0.5,
        0.5,0.5,-0.5,
        -0.5,0.5,0.5,
        0.5,0.5,0.5,
    };
    scanerIndices= { 0,1,
            0,2,
            3,1,
            3,2,

            4,5,
            4,6,
            7,5,
            7,6,

            0,4,
            1,5,
            2,6,
            3,7
        };
    camTarget.setX(roomL/2);
    camTarget.setY(roomH/2);
    camTarget.setZ(roomW/2);
}

void ScanVisualization::setZoom(int percent){
    zoom=percent;
    this->repaint();
}

void ScanVisualization::setCamYaw(float yaw)
{
    if(yaw<=90.0f&&yaw>=-90.0f)
        cameraYaw=yaw;
    this->repaint();

}

void ScanVisualization::setCamPitch(float pitch)
{
    if(pitch<=180.0f&&pitch>=-180.0f)
        cameraPitch=pitch;
    this->repaint();

}

void ScanVisualization::setPointHeight(int x, int z, float height)
{
    roomPoints[3*(x+(xPointsMax+1)*z)+1+3*8]=height;
}

void ScanVisualization::setHeightAt(float x, float z, float h)
{
    setPointHeight(round(x/stepX),round(z/stepZ),h);
}

void ScanVisualization::initializeGL()
{
    f=this->context()->functions();
    ef=this->context()->extraFunctions();
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex, "VertexShader.vert");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment, "FragmentShader.frag");
    shader.bindAttributeLocation("vertex_position",0);
    shader.bindAttributeLocation("vertex_colour",1);
    shader.link();
}

void ScanVisualization::paintGL()
{
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LESS);

    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;   
    QVector3D cameraPosition(zoom*cos(cameraYaw/360*2*M_PI)*sin(cameraPitch/360*2*M_PI),
                             zoom*sin(cameraYaw/360*2*M_PI),
                             zoom*cos(cameraYaw/360*2*M_PI)*cos(cameraPitch/360*2*M_PI));
    cameraPosition+=camTarget;
    QVector3D up(0.0f, 1.0f, 0.0f);

    viewMatrix.lookAt(cameraPosition, camTarget, up);

    projectionMatrix.perspective(45.0f, ((float)this->width())/this->height(), 0.1f, 100.0f);


    f->glViewport(0, 0, this->size().width(), this->size().height());
    shader.bind();
    shader.setUniformValue("view", viewMatrix);
    shader.setUniformValue("projection", projectionMatrix);
    QVector3D colour(1.0,0.0,0.0);
    QVector3D pos(0.0,0.0,0.0);
    drawSmth(roomPoints,roomIndices,colour,pos);
    for(unsigned int i=0;i<scaners->size();i++){
        if(scaners->at(i)->getStatus()==Scaner::working){
            QVector3D colour2(0.0,1.0,0.0);
            drawSmth(scanerPoints,scanerIndices,colour2,scaners->at(i)->getPos());
            std::vector<GLfloat> p3(6);
            p3[0]=scaners->at(i)->getPos().x();
            p3[1]=scaners->at(i)->getPos().y();
            p3[2]=scaners->at(i)->getPos().z();
            p3[3]=scaners->at(i)->getLastScanPoint().x();
            p3[4]=scaners->at(i)->getLastScanPoint().y();
            p3[5]=scaners->at(i)->getLastScanPoint().z();
            std::vector<GLint> i3(2);
            i3[0]=0;
            i3[1]=1;
            drawSmth(p3,i3,colour2,pos);
        }
    }
}

void ScanVisualization::resizeGL(int w,int h)
{
    f->glViewport(0, 0, w, h);
}
