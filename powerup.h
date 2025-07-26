#ifndef POWERUP_H
#define POWERUP_H

#include "config.h"
#include <QTimer>

class HeroPlane;

class PowerUp : public QGraphicsPixmapItem
{
public:
    PowerUp();
    ~PowerUp();

public:
    // 道具初始化
    void init(double x, double y, int type);
    void init_firepower();    // 火力增强道具初始化
    void init_health();       // 生命恢复道具初始化
    void init_bomb();         // 炸弹道具初始化
    void init_shield();       // 护盾强化道具初始化
    void init_exp();          // 经验加成道具初始化

    // 道具销毁
    void destroy();

    // 道具移动
    void move();

    // 判断道具是否存活
    void is_live();

    // 与英雄机碰撞时的效果
    void apply_effect(HeroPlane* heroplane);

public:
    int powerup_type = 1;     // 道具类型
    int status = 0;           // 0表示不可用（已被拾取/销毁），1表示已进入对象池未使用，2表示正在使用
    double speed = POWERUP_SPEED; // 移动速度

    // 道具效果相关
    int health_restore = POWERUP_HEALTH_RESTORE;   // 生命恢复量
    int exp_bonus = POWERUP_EXP_BONUS;             // 经验加成
    int effect_duration = 0;                       // 效果持续时间

    // 特效相关
    QTimer* effect_timer = nullptr;                // 效果计时器（用于持续性效果）
};

#endif // POWERUP_H
