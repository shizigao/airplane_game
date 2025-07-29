#ifndef HEROWEAPON_H
#define HEROWEAPON_H
#include "weapon.h"

class HeroWeapon:public Weapon
{
public:
    HeroWeapon();
    //根据不同的武器种类进行不同的初始化
    void init(int weapon_kind);
    void init1();
    void init2();
    void init3();
    void init4();

public:
    //英雄机武器的种类
    int weapon_kind = 1;
    //武器发射的计时器
    QTimer* weapon_timer = nullptr;
};

#endif // HEROWEAPON_H
