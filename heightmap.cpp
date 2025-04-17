#include "heightmap.h"

HeightMap::HeightMap(int sizex,int sizey) {
    map.resize(sizex);
    for(int i=0;i<sizex;i++)
        map[i].resize(sizey);
}

double HeightMap::getXSize()
{
    return map.size();
}

double HeightMap::getYSize()
{
    return map[0].size();
}

void HeightMap::setHeightAt(int x, int y, double height)
{
    map[x][y]=height;
}

double HeightMap::getHeightAt(int x, int y)
{
    return map[x][y];
}
