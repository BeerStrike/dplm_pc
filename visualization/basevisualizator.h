#ifndef BASEVISUALIZATOR_H
#define BASEVISUALIZATOR_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QVector>
class BaseVisualizator : public QObject
{
    Q_OBJECT
private:
    //GLuint cords_buff;
    //GLuint indices_buff;
    //GLuint vao;
protected:
    QOpenGLContext *my_context;
    QOpenGLShaderProgram *sh;
    QOpenGLFunctions *f;
    QOpenGLExtraFunctions *ef;
    GLuint createCordsBuff(QVector<GLdouble> &points);
    GLuint createIndicesBuff(QVector<GLuint> &indices);
public:
    explicit BaseVisualizator(QObject *parent = nullptr);
    void initalize(QOpenGLContext *context,QOpenGLShaderProgram *shader);
    virtual void draw()=0;
    ~BaseVisualizator();
signals:
};

#endif // BASEVISUALIZATOR_H
