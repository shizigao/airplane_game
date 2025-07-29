#ifndef WEAPON_H
#define WEAPON_H
#include "config.h"

class Weapon:public QGraphicsPixmapItem
{
public:
    Weapon();

public:
    //武器发射间隔
    int interval = 10;
    //子弹是否连续发射（是否按下对应攻击键）
    bool is_continuously_shooting = false;
};

#endif // WEAPON_H
