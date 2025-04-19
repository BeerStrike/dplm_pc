#include "combinatedheightmap.h"

CombinatedHeightMap::CombinatedHeightMap(float length,float width,float step,QObject *parent)
    : BaseHeightMap{parent},l(length),w(width),stp(step)
{}

int CombinatedHeightMap::getXSize()
{
    return round(l/stp)+1;
}

int CombinatedHeightMap::getYSize()
{
    return round(w/stp)+1;
}

float CombinatedHeightMap::getLength()
{
    return l;
}

float CombinatedHeightMap::getWidth()
{
    return w;
}

float CombinatedHeightMap::getStep()
{
    return stp;
}

float CombinatedHeightMap::getHeightAt(float x, float y)
{
    int height=0;
    int minDist=INT_MAX;
    QVector3D p(x,y,0);
    for(int i=0;i<hmv.size();i++){
        float d=scposv[i].distanceToPoint(p);
        if(d<minDist){
            minDist=d;
            height=hmv[i]->getHeightAt(x,y);
        }
    }
}

float CombinatedHeightMap::getHeightAtPoint(int x, int y)
{
    getHeightAt(round(x/stp),round(y/stp));
}

void CombinatedHeightMap::addHeightMap(BaseHeightMap *hm, QVector3D scpos)
{
    hmv.push_back(hm);
    scposv.push_back(scpos);
}
