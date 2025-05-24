#include "axisvisualizartor.h"

AxisVisualizartor::AxisVisualizartor(ScanController *scController,QObject *parent)
    : BaseVisualizator{scController,parent} {
    points={
        0.0,0.0,0.0,
        1.0,0.0,0.0,
        0.0,0.0,1.0,
        0.0,1.0,0.0,
    };
    indices= {
        0,1,
        0,2,
        0,3,
    };
}

void AxisVisualizartor::draw()
{
    QMatrix4x4 modelMatrix;
    QVector3D scale;
    scale.setX(2*scCtrl->getRoom()->getRoomWidth());
    scale.setY(2*scCtrl->getRoom()->getRoomHeight());
    scale.setZ(2*scCtrl->getRoom()->getRoomLength());
    modelMatrix.scale(scale);
    QVector3D colour(0.0,0.0,0.0);
    QVector3D pos(0.0,0.0,0.0);
    modelMatrix.translate(pos);
    sh->setUniformValue("model", modelMatrix);
    sh->setUniformValue("colour",colour);

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
