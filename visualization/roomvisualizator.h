#ifndef ROOMVISUALIZATOR_H
#define ROOMVISUALIZATOR_H

#include "basevisualizator.h"
#include <room.h>
class RoomVisualizator : public BaseVisualizator
{
    Q_OBJECT
private:
    QVector<GLdouble> points;
    QVector<GLuint> indices;
public:
    explicit RoomVisualizator(Room *room,QObject *parent = nullptr);
    void draw() override;

};

#endif // ROOMVISUALIZATOR_H
