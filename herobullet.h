#ifndef HEROBULLET_H
#define HEROBULLET_H
#include "bullet.h"
#include "heroweapon.h"
#include "QList"

class EnemyPlane;

class HeroBullet: public Bullet
{
public:
    HeroBullet();
public:
    //子弹种类
    int bullet_kind = 1;

    void init(double x, double y, int kind);//每次从队列中取出或创建时子弹时需要初始化（主要是初始化图片，子弹数值由武器数值决定）
    void init_1();//第一种子弹的初始化
    void init_2();//第二种子弹的初始化
    void init_3();//第三种子弹的初始化
    void init_4();//第四种子弹的初始化
    //1是正常子弹，2是正弦函数移动的子弹，3是穿甲弹，4是追踪弹


    void destroy();//子弹的销毁（设置为不可见），子弹失效后要调用此函数

    void move(QList<EnemyPlane*>& enemyplane_pool);//子弹的移动总函数，具体移动函数由kind决定
    void move_1();//第一种子弹的移动函数，直接向前移动
    void move_2();//第二种子弹的移动函数，正弦函数移动
    void move_3();//第三种子弹的移动函数，能够穿过敌人
    void move_4(QList<EnemyPlane*>& enemyplane_pool);//第四种子弹的移动函数，能够追踪敌人

    //判断子弹是否存活的函数
    void is_live();
    //根据武器数值改变子弹数值
    void set_value(HeroWeapon* heroweapon);

    //碰撞事件
    void collide_with_enemyplane(EnemyPlane* enemyplane);

    double amplitude;   // 曲线摆动幅度（横向偏移最大值）
    double frequency;   // 曲线摆动频率（值越大摆动越频繁）

};

#endif // HEROBULLET_H
