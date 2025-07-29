#ifndef HEROBULLET_H
#define HEROBULLET_H
#include "bullet.h"

class HeroBullet: public Bullet
{
public:
    HeroBullet();
    //不同的初始化函数
    void init(int bullet_kind);
    void init1();
    void init2();
    void init3();
    void init4();
public:
    //英雄机子弹的种类
    int bullet_kind = 1;

};

#endif // HEROBULLET_H
