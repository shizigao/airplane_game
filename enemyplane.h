#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "plane.h"
#include "enemyweapon.h"
#include "enemybulletpool.h"
#include "herobullet.h"
class EnemyPlane:public Plane
{
public:
    EnemyPlane();
    //初始化函数
    void init(int plane_kind);
    void init1();
    void init2();
    void init3();
    void init4();

    //移动函数
    void move();
    void move1();
    void move2();
    void move3();
    void move4();

    //发射子弹
    void weapon_shoot(EnemyBulletPool* enemybullet_pool, QGraphicsScene* level_scene);

    //销毁函数
    void destroy();

    //碰撞函数
    void collide_with_herobullet(HeroBullet* herobullet);

    //判断生命值是否小于零0
    void is_live();

public:
    //种类
    int plane_kind = 1;
    //武器槽
    EnemyWeapon* weapon = nullptr;



};

#endif // ENEMYPLANE_H
