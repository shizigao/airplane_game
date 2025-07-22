#ifndef HEROPLANE_H
#define HEROPLANE_H

#include "plane.h"
#include "heroweapon.h"
class HeroPlane: public Plane
{
public:
    HeroPlane();
    HeroPlane(double x, double y, QPixmap pixmap);

    //飞机移动（判断是否越界）
    void move_to(double x, double y);

    //发射武器子弹
    void weapon1_shoot();
    void weapon2_shoot();
    void weapon3_shoot();

public:
    HeroWeapon* weapon1 = nullptr, *weapon2 = nullptr, *weapon3 = nullptr;//英雄机的三个武器

};

#endif // HEROPLANE_H
