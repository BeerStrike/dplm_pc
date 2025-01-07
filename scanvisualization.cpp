#include "scanvisualization.h"
#include <QMatrix4x4>
#include <QVector3D>
#include <iostream>

ScanVisualization::ScanVisualization(QWidget *pwgt,std::vector<Scaner> *scenerVec,float roomL,float xStep,float roomW,float zStep,float roomH):QOpenGLWidget(pwgt){
    xPointsMax=roomL/xStep;
    zPointsMax=roomW/zStep;
    scaners=scanerVec;
    zoom=5;
    cameraYaw=45.0f;
    cameraPitch=0;
    points={
        -roomL/2,0,-roomW/2,
        roomL/2,0,-roomW/2,
        -roomL/2,0,roomW/2,
        roomL/2,0,roomW/2,

        -roomL/2,roomH,-roomW/2,
        roomL/2,roomH,-roomW/2,
        -roomL/2,roomH,roomW/2,
        roomL/2,roomH,roomW/2,
    };
    for(int i=0;i<=xPointsMax;i++)
        for(int j=0;j<=zPointsMax;j++){
            points.push_back(-roomL/2+i*(roomL/xPointsMax));
            points.push_back(0);
            points.push_back(-roomW/2+j*(roomW/zPointsMax));
        }
    indices= {  0,1,
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
                indices.push_back(8+i+j*(xPointsMax+1));
                indices.push_back(8+i+(xPointsMax+1)+j*(xPointsMax+1));
                indices.push_back(8+i+j*(xPointsMax+1));
                indices.push_back(8+i+1+j*(xPointsMax+1));

            }
    }
    camTarget.setX(0.0f);
    camTarget.setY(roomH/2);
    camTarget.setZ(0.0f);
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
    points[3*(x+(xPointsMax+1)*z)+1+3*8]=height;
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

    QMatrix4x4 modelMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;
    modelMatrix.scale(1.0f);
    modelMatrix.translate(0.0,0.0,0.0);

    QVector3D cameraPosition(zoom*cos(cameraYaw/360*2*M_PI)*sin(cameraPitch/360*2*M_PI),
                             zoom*sin(cameraYaw/360*2*M_PI),
                             zoom*cos(cameraYaw/360*2*M_PI)*cos(cameraPitch/360*2*M_PI));
    QVector3D up(0.0f, 1.0f, 0.0f);

    viewMatrix.lookAt(cameraPosition, camTarget, up);

    projectionMatrix.perspective(45.0f, ((float)this->width())/this->height(), 0.1f, 100.0f);


    f->glViewport(0, 0, this->size().width(), this->size().height());
    shader.bind();
    shader.setUniformValue("model", modelMatrix);
    shader.setUniformValue("view", viewMatrix);
    shader.setUniformValue("projection", projectionMatrix);

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

void ScanVisualization::resizeGL(int w,int h)
{
    f->glViewport(0, 0, w, h);
}
