#include "basevisualizator.h"


BaseVisualizator::BaseVisualizator(ScanController *scController,QObject *parent)
    : QObject{parent},scCtrl(scController)
{}

void BaseVisualizator::initalize(QOpenGLContext *context,QOpenGLShaderProgram *shader)
{
    my_context=context;
    sh=shader;
    f=my_context->functions();
    ef=my_context->extraFunctions();
}

GLuint BaseVisualizator::createCordsBuff(QVector<GLfloat> &points)
{
    GLuint cords_buff = 0;
    f->glGenBuffers(1, &cords_buff);
    f->glBindBuffer(GL_ARRAY_BUFFER, cords_buff);
    ef->glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(GLfloat), &(points[0]), GL_STATIC_DRAW);
    return cords_buff;
}

GLuint BaseVisualizator::createIndicesBuff(QVector<GLuint> &indices){
    GLuint indices_buff=0;
    f->glGenBuffers(1, &indices_buff);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buff);
    ef->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &(indices[0]), GL_STATIC_DRAW);
    return indices_buff;
}
