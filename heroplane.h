#ifndef HEROPLANE_H
#define HEROPLANE_H

#include "plane.h"
#include "heroweapon.h"
#include "enemybullet.h"
#include "enemyplane.h"
#include <QTimer>
#include <QLineEdit>
class HeroPlane: public Plane
{
public:
    HeroPlane(QTimer *invincible_timer);
    ~HeroPlane();

    //飞机移动(保证不越界）
    void move_to(double x, double y);
    //英雄机初始化
    void init(double x, double y, int kind);
    void init1();
    void init2();
    void init3();
    void init4();

    //发射武器子弹
    void weapon1_shoot();
    void weapon2_shoot();
    void weapon3_shoot();

    //碰撞事件
    //被敌机子弹击中
    void collide_with_enemybullet(EnemyBullet* enemybullet);//传入击中的敌机子弹
    //与敌机相互碰撞
    void collide_with_enemyplane(EnemyPlane* enemyplane);//传入碰撞的敌机
    //判断英雄机是否存活
    void is_live();
    //判断英雄是否升级
    bool is_upgrade();
    //升级
    void upgrade();

public:
    HeroWeapon* weapon1 = nullptr, *weapon2 = nullptr, *weapon3 = nullptr;//英雄机的三个武器
    //英雄机的状态
    int status = 0;//0表示未使用（已死亡）,2表示正在使用（存活）
    //英雄机的种类
    int plane_kind = 1;
    //英雄机计时器
    //无敌状态的计时器
    QTimer *invincible_timer = nullptr;

    //护盾图片
    QGraphicsPixmapItem *shield = nullptr;
    //升级后显示的图片
    QGraphicsPixmapItem* level_up_text = nullptr;

    //当前经验值
    int experience = 0;
    //下一次升级所需经验值
    int next_level_experience = UPGRADE_EXPERIENCE;
    //等级
    int level = 1;
    double rate_sum = 1;//数值总提升比率

    //炸弹
    int bomb_count = 1;  // 初始炸弹数量
    int max_bomb_count = 5;  // 最大炸弹数量


};

#endif // HEROPLANE_H
