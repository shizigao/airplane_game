#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include "plane.h"
#include "enemyweapon.h"
class EnemyPlane: public Plane
{
public:

    EnemyPlane(QTimer* weapon_timer);



    void init(double x, double y, int kind);//每次从队列中取出或创建时敌机时需要初始化,init会自动开启计时器
    void init_1();//第一种敌机的初始化
    void init_2();//第二种敌机的初始化
    void init_3();//第三种敌机的初始化
    void init_4();//第四种敌机的初始化

    void destroy();//敌机的销毁，敌机死亡后要调用此函数

    void move();//敌机的移动总函数，具体移动函数由kind决定
    void move_1();//第一种敌机的移动函数，直接向前移动
    void move_2();//第二种敌机的移动函数
    void move_3();//第三种敌机的移动函数
    void move_4();//第四种敌机的移动函数


    //判断敌机是否存活的函数
    void is_live();

public:
    int plane_kind = 1;//kind表示敌机的种类
    EnemyWeapon* weapon;//敌机的武器
    QTimer *weapon_timer;//敌机武器的计时器，需在创建敌机时手动初始化

};

#endif // ENEMYPLANE_H
