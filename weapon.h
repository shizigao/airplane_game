#ifndef WEAPON_H
#define WEAPON_H
#include "config.h"
#include <QTimer>

class Weapon: public QGraphicsPixmapItem
{

public:
    Weapon();

public:
    //武器子弹的伤害
    double damage = 10;
    //武器的发射间隔
    int interval = 1000;//单位:ms
    //武器子弹的移动速度
    double speed = 30;
    //武器的碰撞箱
    QRect rect();

    //子弹是否可发射
    bool is_ready = true;





};

#endif // WEAPON_H
