#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include <vector>
class HeightMap
{
private:
    std::vector<std::vector<double>> map;
public:
    HeightMap(int sizex,int sizey);
    double getXSize();
    double getYSize();
    void setHeightAt(int x,int y,double height);
    double getHeightAt(int x,int y);
};

#endif // HEIGHTMAP_H
