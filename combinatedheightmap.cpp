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
    float height=0;
    int n=0;
    for(int i=0;i<hmv.size();i++){
        float h=hmv[i]->getHeightAt(x,y);
        if(h!=0){
            height+=h;
            n++;
        }
    }
    if(n>0)
        return height/n;
    else
        return 0;
}

void CombinatedHeightMap::addHeightMap(BaseHeightMap *hm, QVector3D scpos)
{
    hmv.push_back(hm);
    scposv.push_back(scpos);
}
