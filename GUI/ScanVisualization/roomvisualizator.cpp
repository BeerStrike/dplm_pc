#include "roomvisualizator.h"

RoomVisualizator::RoomVisualizator(ScanController *scController,QObject *parent)
    : BaseVisualizator{scController,parent}
{
    points={
        0,0,0,
        1,0,0,
        0,0,1,
        1,0,1,

        0,1,0,
        1,1,0,
        0,1,1,
        1,1,1,
    };
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
}

void RoomVisualizator::draw()
{
    QMatrix4x4 modelMatrix;
    QVector3D scale;
    scale.setX(scCtrl->getRoom()->getRoomWidth());
    scale.setY(scCtrl->getRoom()->getRoomHeight());
    scale.setZ(scCtrl->getRoom()->getRoomLength());
    modelMatrix.scale(scale);
    sh->setUniformValue("model", modelMatrix);
    QVector3D colour(1.0,0.0,0.0);

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
