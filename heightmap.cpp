#include "heightmap.h"
#include <cmath>

HeightMap::HeightMap(float length,float width,float step,QObject *parent):BaseHeightMap{parent} {
    int sizex=round(length/step)+1;
    int sizey=round(width/step)+1;
    l=length;
    w=width;
    stp=step;
    map.resize(sizex);
    for(int i=0;i<sizex;i++)
        map[i].resize(sizey);
}

float HeightMap::getLength()
{
    return l;
}

float HeightMap::getWidth()
{
    return w;
}

float HeightMap::getStep()
{
    return stp;
}

void HeightMap::addPoint(QVector3D point)
{
    if(point.x()>=0&&point.x()<=l&&point.y()>=0&&point.y()<=w){
        int xind=round(point.x()/stp);
        int yind=round(point.y()/stp);
        map[xind][yind].push_back(point);
        float max=INT_MIN;
        for(int i=0;i<map[xind][yind].size();i++)
            if(map[xind][yind][i].z()>max)
                max=map[xind][yind][i].z();
        QVector<QVector3D> v2;
        for(int i=0;i<map[xind][yind].size();i++)
            if(map[xind][yind][i].z()>(max-stp))
                v2.push_back(map[xind][yind][i]);
        map[xind][yind]=v2;
    }
}

float HeightMap::getHeightAt(float x, float y)
{
    QVector<QVector3D> pointsNear;
    int xind=round(x/stp);
    int yind=round(y/stp);
    for(int i=0;i<map[xind][yind].size();i++)
        pointsNear.push_back(map[xind][yind][i]);
    if(pointsNear.size()>0){
        float h=0;
        for(int i=0;i<pointsNear.size();i++){
            h+=pointsNear[i].z();
        }
        return h/pointsNear.size();
    }else{
        return 0;
    }
}
