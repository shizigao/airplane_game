#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "plane.h"

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

    //销毁函数
    void destroy();
public:
    //种类
    int plane_kind = 1;
};

#endif // ENEMYPLANE_H
