#include "scanervisualizator.h"
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

void ScanerVisualizator::genergatePointsAndIndices(QVector<GLfloat> &points,QVector<GLuint> &indices){
    for(unsigned int i=0;i<(unsigned int)scCtrl->getScanersNum();i++){
        QVector<GLfloat> poi;
        QVector<GLuint> ind;
        switch (scCtrl->getScaner(i)->getDirection()){
            case Scaner::xdyd:
                poi={
                    scCtrl->getScaner(i)->getPos().y(), scCtrl->getScaner(i)->getPos().z(), scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y()+SCANER_LENGTH,scCtrl->getScaner(i)->getPos().z(), scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y(),scCtrl->getScaner(i)->getPos().z(),SCANER_WIDTH+ scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y()+SCANER_LENGTH,scCtrl->getScaner(i)->getPos().z(),SCANER_WIDTH+ scCtrl->getScaner(i)->getPos().x(),

                    scCtrl->getScaner(i)->getPos().y(),scCtrl->getScaner(i)->getPos().z()-SCANER_HEIGHT, scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y()+SCANER_LENGTH,scCtrl->getScaner(i)->getPos().z()-SCANER_HEIGHT, scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y(),scCtrl->getScaner(i)->getPos().z()-SCANER_HEIGHT,SCANER_WIDTH+ scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y()+SCANER_LENGTH,scCtrl->getScaner(i)->getPos().z()-SCANER_HEIGHT,SCANER_WIDTH+ scCtrl->getScaner(i)->getPos().x(),

                    scCtrl->getScaner(i)->getLastScanPoint().y(),scCtrl->getScaner(i)->getLastScanPoint().z(),scCtrl->getScaner(i)->getLastScanPoint().x()
                };
                break;
            case Scaner::xryd:

                break;
            case Scaner::xdyr:

                break;
            case Scaner::xryr:
                poi={
                    scCtrl->getScaner(i)->getPos().y(), scCtrl->getScaner(i)->getPos().z(), scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y()-SCANER_LENGTH,scCtrl->getScaner(i)->getPos().z(), scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y(),scCtrl->getScaner(i)->getPos().z(),scCtrl->getScaner(i)->getPos().x()-SCANER_WIDTH,
                    scCtrl->getScaner(i)->getPos().y()-SCANER_LENGTH,scCtrl->getScaner(i)->getPos().z(),scCtrl->getScaner(i)->getPos().x()-SCANER_WIDTH,

                    scCtrl->getScaner(i)->getPos().y(),scCtrl->getScaner(i)->getPos().z()-SCANER_HEIGHT, scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y()-SCANER_LENGTH,scCtrl->getScaner(i)->getPos().z()-SCANER_HEIGHT, scCtrl->getScaner(i)->getPos().x(),
                    scCtrl->getScaner(i)->getPos().y(),scCtrl->getScaner(i)->getPos().z()-SCANER_HEIGHT,scCtrl->getScaner(i)->getPos().x()-SCANER_WIDTH,
                    scCtrl->getScaner(i)->getPos().y()-SCANER_LENGTH,scCtrl->getScaner(i)->getPos().z()-SCANER_HEIGHT,scCtrl->getScaner(i)->getPos().x()-SCANER_WIDTH,

                    scCtrl->getScaner(i)->getLastScanPoint().y(),scCtrl->getScaner(i)->getLastScanPoint().z(),scCtrl->getScaner(i)->getLastScanPoint().x()
                };
            break;
        }

        ind= {i*9+0,i*9+1,
            i*9+0,i*9+2,
            i*9+3,i*9+1,
            i*9+3,i*9+2,

            i*9+4,i*9+5,
            i*9+4,i*9+6,
            i*9+7,i*9+5,
            i*9+7,i*9+6,

            i*9+0,i*9+4,
            i*9+1,i*9+5,
            i*9+2,i*9+6,
            i*9+3,i*9+7,
        };
        switch (scCtrl->getScaner(i)->getDirection()){
            case Scaner::xdyd:
            ind.push_back(i*9+7);
                break;
            case Scaner::xryd:

                break;
            case Scaner::xdyr:

                break;
            case Scaner::xryr:
                ind.push_back(i*9+7);
                break;
        }
        ind.push_back(i*9+8);
        for(int j=0;j<poi.size();j++)
            points.push_back(poi[j]);
        for(int j=0;j<ind.size();j++)
            indices.push_back(ind[j]);
    }
}
ScanerVisualizator::ScanerVisualizator(ScanController *scController,QObject *parent)
    : BaseVisualizator{scController,parent} {
}

void ScanerVisualizator::draw(){
    if(scCtrl->getScanersNum()==0)
        return;
    QMatrix4x4 modelMatrix;
    modelMatrix.scale(1.0f);
    sh->setUniformValue("model", modelMatrix);
    QVector3D colour;
    colour.setX(0.0);
    colour.setY(1.0);
    colour.setZ(0.0);
    sh->setUniformValue("colour",colour);
    QVector3D pos(0.0,0.0,0.0);
    modelMatrix.translate(pos);
    QVector<GLfloat> points;
    QVector<GLuint> indices;
    genergatePointsAndIndices(points,indices);
    GLuint coords_vbo = createCordsBuff(points);
    GLuint elementbuffer=createIndicesBuff(indices);
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
