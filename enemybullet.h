#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include "bullet.h"
#include "enemyweapon.h"
class HeroPlane;
class EnemyBullet: public Bullet
{
public:
    EnemyBullet();

public:
    //子弹种类
    int bullet_kind = 1;

    void init(double x, double y, int kind);//每次从队列中取出或创建时子弹时需要初始化（主要是初始化图片，子弹数值由武器数值决定）
    void init_1();//第一种子弹的初始化
    void init_2();//第二种子弹的初始化
    void init_3();//第三种子弹的初始化
    void init_4();//第四种子弹的初始化
    void init_boss_bullet_1();//Boss子弹1的初始化
    void init_boss_bullet_2();//Boss子弹2的初始化
    void init_boss_bullet_3();//Boss子弹3的初始化

    void destroy();//子弹的销毁（设置为不可见），子弹失效后要调用此函数

    void move(HeroPlane* heroplane1, HeroPlane* heroplane2);//子弹的移动总函数，具体移动函数由kind决定
    void move_1();//第一种子弹的移动函数，直接向前移动
    void move_2();//第二种子弹的移动函数
    void move_3();//第三种子弹的移动函数
    void move_4(HeroPlane* heroplane1, HeroPlane* heroplane2);//第四种子弹的移动函数
    void move_boss_bullet_1();//Boss子弹1的移动函数：直线快速移动
    void move_boss_bullet_2();//Boss子弹2的移动函数：波浪形移动
    void move_boss_bullet_3(HeroPlane* heroplane1, HeroPlane* heroplane2);//Boss子弹3的移动函数：激光直线移动

    //判断子弹是否存活的函数
    void is_live();
    //根据武器数值改变子弹数值
    void set_value(EnemyWeapon* enemyweapon);

    //碰撞事件
    void collide_with_heroplane(HeroPlane* heroplane);
};

#endif // ENEMYBULLET_H
