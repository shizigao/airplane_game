#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include "bullet.h"
#include "enemyweapon.h"
class EnemyBullet:public Bullet
{
public:
    EnemyBullet();

    //不同的初始化函数
    void init(int bullet_kind, EnemyWeapon* enemyweapon);
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

};

#endif // ENEMYBULLET_H
