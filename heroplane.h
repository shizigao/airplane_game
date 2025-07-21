#ifndef HEROPLANE_H
#define HEROPLANE_H

#include "plane.h"

class HeroPlane: public Plane
{
public:
    HeroPlane();
    HeroPlane(int x, int y, QPixmap pixmap);

    //飞机移动（判断是否越界）
    void move_to(double x, double y);

};

#endif // HEROPLANE_H
