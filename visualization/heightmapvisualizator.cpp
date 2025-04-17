#include "heightmapvisualizator.h"

void HeightMapVisualizator::heigntMapToPoints(QVector<GLdouble> &points,QVector<GLuint> &indices)
{
    points.clear();
    indices.clear();
    int xm=hm->getXSize();
    int ym=hm->getYSize();

    for(int i=0;i<xm;i++)
        for(int j=0;j<ym;j++){
            points.push_back(i*stp);
            points.push_back(hm->getHeightAt(i,j));
            points.push_back(j*stp);
        }
    for(int i=0;i<xm;i++){
        for(int j=0;j<ym;j++){
           if(i!=xm-1){
               indices.push_back(i*ym+j);
               indices.push_back((i+1)*ym+j);
            }
           if(j!=ym-1){
               indices.push_back(i*ym+j);
               indices.push_back((i)*ym+j+1);
           }
        }
    }
}

HeightMapVisualizator::HeightMapVisualizator(HeightMap * heightMap,double step,QObject *parent)
    : BaseVisualizator{parent}
{
    hm=heightMap;
    stp=step;
}

void HeightMapVisualizator::draw()
{
    QMatrix4x4 modelMatrix;
    modelMatrix.scale(1.0f);
    QVector3D pos(0.0,0.0,0.0);
    QVector3D colour(0.0,0.0,1.0);
    modelMatrix.translate(pos);
    sh->setUniformValue("model", modelMatrix);
    sh->setUniformValue("colour",colour);
    QVector<GLdouble> points;
    QVector<GLuint> indices;
    heigntMapToPoints(points,indices);
    GLuint coords_vbo = createCordsBuff(points);
    GLuint elementbuffer=createIndicesBuff(indices);
    GLuint vao = 0;
    ef->glGenVertexArrays(1, &vao);
    ef->glBindVertexArray(vao);
    f->glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
    f->glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    ef->glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);

    ef->glDeleteVertexArrays(1, &vao);
    f->glDeleteBuffers(1, &coords_vbo);
    f->glDeleteBuffers(1, &elementbuffer);
}
