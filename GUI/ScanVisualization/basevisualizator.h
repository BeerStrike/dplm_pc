#ifndef BASEVISUALIZATOR_H
#define BASEVISUALIZATOR_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QVector>
#include "scancontroller.h"

class BaseVisualizator : public QObject
{
    Q_OBJECT
protected:
    ScanController *scCtrl;
    QOpenGLContext *my_context;
    QOpenGLShaderProgram *sh;
    QOpenGLFunctions *f;
    QOpenGLExtraFunctions *ef;
    GLuint createCordsBuff(QVector<GLfloat> &points);
    GLuint createIndicesBuff(QVector<GLuint> &indices);
public:
    explicit BaseVisualizator(ScanController *scController,QObject *parent = nullptr);
    void initalize(QOpenGLContext *context,QOpenGLShaderProgram *shader);
    virtual void draw()=0;
};

#endif // BASEVISUALIZATOR_H
