#ifndef HEROBULLET_H
#define HEROBULLET_H
#include "bullet.h"
#include "heroweapon.h"
class HeroBullet: public Bullet
{
public:
    HeroBullet();
    //不同的初始化函数
    void init(int bullet_kind, HeroWeapon* heroweapon);
    void init1();
    void init2();
    void init3();
    void init4();
public:
    //英雄机子弹的种类
    int bullet_kind = 1;
    //移动函数
    void move();
    void move1();
    void move2();
    void move3();
    void move4();
    //子弹的销毁函数
    void destroy();

    //英雄机子弹碰撞函数
    void collide_with_enemyplane();


};

#endif // HEROBULLET_H
