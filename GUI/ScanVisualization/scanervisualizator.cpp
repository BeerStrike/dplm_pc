#include "scanervisualizator.h"
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

ScanerVisualizator::ScanerVisualizator(ScanController *scController,QObject *parent)
    : BaseVisualizator{scController,parent} {
    colour.setX(0.0);
    colour.setY(1.0);
    colour.setZ(0.0);
    points={
        0,-SCANER_HEIGHT,0,
        SCANER_LENGTH,-SCANER_HEIGHT,0,
        0,-SCANER_HEIGHT,SCANER_WIDTH,
        SCANER_LENGTH,-SCANER_HEIGHT,SCANER_WIDTH,

        0,0,0,
        SCANER_LENGTH,0,0,
        0,0,SCANER_WIDTH,
        SCANER_LENGTH,0,SCANER_WIDTH,
    };
    indices= { 0,1,
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
}

void ScanerVisualizator::draw(){

    for(unsigned int i=0;i<scCtrl->getScanersNum();i++){
        QMatrix4x4 modelMatrix;
        modelMatrix.scale(1.0f);
        QVector3D scanerPos;
        scanerPos.setX(scCtrl->getScaner(i)->getPos().y());
        scanerPos.setY(scCtrl->getScaner(i)->getPos().z());
        scanerPos.setZ(scCtrl->getScaner(i)->getPos().x());
        modelMatrix.translate(scanerPos);
        sh->setUniformValue("model", modelMatrix);
        sh->setUniformValue("colour",colour);

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
}
