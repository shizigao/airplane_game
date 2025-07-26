#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include "plane.h"
#include "enemyweapon.h"

class HeroBullet;
class HeroPlane;
class EnemyPlane: public Plane
{
public:

    EnemyPlane(QTimer* weapon_timer);
    ~EnemyPlane();


    void init(double x, double y, int kind);//每次从队列中取出或创建时敌机时需要初始化,init会自动开启计时器
    void init_1();//第一种敌机的初始化
    void init_2();//第二种敌机的初始化
    void init_3();//第三种敌机的初始化
    void init_4();//第四种敌机的初始化
    void init_boss1();//第一个Boss的初始化
    void init_boss2();//第二个Boss的初始化

    void destroy();//敌机的销毁，敌机死亡后要调用此函数

    void move(HeroPlane* heroplane1, HeroPlane* heroplane2);//敌机的移动总函数，具体移动函数由kind决定(要传入两个英雄机指针)
    void move_1();//第一种敌机的移动函数，直接向前移动
    void move_2();//第二种敌机的移动函数
    void move_3();//第三种敌机的移动函数
    void move_4(HeroPlane* heroplane1, HeroPlane* heroplane2);//第四种敌机的移动函数，朝最近的英雄机方向移动
    void move_boss1();//Boss1的移动函数
    void move_boss2();//Boss2的移动函数

    //Boss相关函数
    bool is_boss();//判断是否为Boss
    void update_boss_phase();//更新Boss阶段
    void boss_attack_pattern_1();//Boss攻击模式1：直线攻击
    void boss_attack_pattern_2();//Boss攻击模式2：散弹攻击
    void boss_attack_pattern_3();//Boss攻击模式3：弹幕攻击
    void boss_special_attack();//Boss特殊攻击（每个阶段的特色攻击）

    //判断敌机是否存活的函数
    void is_live();

    //碰撞事件
    //被敌机子弹击中
    void collide_with_herobullet(HeroBullet* herobullet);//传入击中的英雄机子弹
    //与敌机相互碰撞
    void collide_with_heroplane(HeroPlane* heroplane);//传入碰撞的英雄机

public:
    int plane_kind = 1;//kind表示敌机的种类，5=Boss1, 6=Boss2
    EnemyWeapon* weapon = nullptr;//敌机的武器
    QTimer *weapon_timer = nullptr;//敌机武器的计时器，需在创建敌机时手动初始化

    //子弹发射间隔
    double fire_interval = 1000;//单位:ms
    //被击败后的得分
    int score = 100;

    //Boss相关属性
    int boss_phase = 1;//Boss当前阶段(1, 2, 3)
    int max_health = 0;//Boss的最大生命值
    int attack_pattern_timer = 0;//攻击模式计时器
    int movement_timer = 0;//移动模式计时器
    bool is_entering = true;//Boss是否正在进入场景
    double target_x = 0;//Boss的目标X坐标
    double target_y = 0;//Boss的目标Y坐标
    int special_attack_cooldown = 0;//特殊攻击冷却时间

    static double difficulty_degree;//难度系数

};

#endif // ENEMYPLANE_H
