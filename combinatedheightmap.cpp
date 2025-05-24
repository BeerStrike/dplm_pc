#include "combinatedheightmap.h"

CombinatedHeightMap::CombinatedHeightMap(float length,float width,float step,QObject *parent)
    : BaseHeightMap{parent},l(length),w(width),stp(step)
{}


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
    float height=INT_MAX;
    for(int i=0;i<hmv.size();i++){
        float h=hmv[i]->getHeightAt(x,y);
        if(h<height){
            height=h;
        }
    }
    if(height==INT_MAX)
        return 0;
    else
        return height;
}

void CombinatedHeightMap::addHeightMap(BaseHeightMap *hm, QVector3D scpos)
{
    hmv.push_back(hm);
    scposv.push_back(scpos);
}
