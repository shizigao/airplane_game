#ifndef HEROPLANE_H
#define HEROPLANE_H
#include "plane.h"
#include "heroweapon.h"
#include "herobullet.h"
#include "herobulletpool.h"

class HeroPlane:public Plane
{
public:
    HeroPlane();
    //根据不同的英雄机种类初始化英雄机
    void init(int heroplane_kind);
    void init_1();
    void init_2();

    //发射第一个武器的子弹
    void weapon1_shoot(HeroBulletPool* herobullet_pool, QGraphicsScene* level_scene);
    //发射第二个武器的子弹
    void weapon2_shoot(HeroBulletPool* herobullet_pool, QGraphicsScene* level_scene);
    //发射第三个武器的子弹
    void weapon3_shoot(HeroBulletPool* herobullet_pool, QGraphicsScene* level_scene);
public:
    //英雄机的种类
    int heroplane_kind = 1;
    //英雄机的三个武器槽
    HeroWeapon *weapon1 = nullptr, *weapon2 = nullptr, *weapon3 = nullptr;


};

#endif // HEROPLANE_H
