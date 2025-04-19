#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include <vector>
#include "baseheightmap.h"

class HeightMap:BaseHeightMap
{
    Q_OBJECT
private:
    std::vector<std::vector<float>> map;
    float stp;
public:
    HeightMap(float length,float width,float step,QObject *parent = nullptr);
    int getXSize() override;
    int getYSize() override;
    float getLength() override;
    float getWidth() override;
    float getStep() override;
    void setHeightAtPoint(int x,int y,float height);
    void setHeightAt(float x,float y,float height);
    float getHeightAt(float x,float y) override;
    float getHeightAtPoint(int x,int y) override;
};

#endif // HEIGHTMAP_H
