#include "heightmap.h"
#include <cmath>
HeightMap::HeightMap(float length,float width,float step,QObject *parent):BaseHeightMap{parent} {
    int sizex=round(length/step)+1;
    int sizey=round(width/step)+1;
    stp=step;
    map.resize(sizex);
    for(int i=0;i<sizex;i++)
        map[i].resize(sizey);
}

int HeightMap::getXSize()
{
    return map.size();
}

int HeightMap::getYSize()
{
    return map[0].size();
}

float HeightMap::getLength()
{
    return stp*getXSize();
}

float HeightMap::getWidth()
{
    return stp*getYSize();
}

float HeightMap::getStep()
{
    return stp;
}

void HeightMap::setHeightAtPoint(int x, int y, float height)
{
    map[x][y]=height;

}

void HeightMap::setHeightAt(float x, float y, float height)
{
    setHeightAtPoint(round(x/stp),round(y/stp),height);
}

float HeightMap::getHeightAt(float x, float y)
{
    return getHeightAtPoint(round(x/stp),round(y/stp));
}

float HeightMap::getHeightAtPoint(int x, int y)
{
    return map[x][y];
}


