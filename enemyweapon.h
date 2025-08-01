#ifndef ENEMYWEAPON_H
#define ENEMYWEAPON_H
#include "weapon.h"

class EnemyWeapon:public Weapon
{
public:
    EnemyWeapon();

    //根据不同的武器种类进行不同的初始化
    void init(int weapon_kind);
    void init1();
    void init2();
    void init3();
    void init4();

public:
    //敌机武器的种类
    int weapon_kind = 1;
    //武器发射的计时器
    QTimer* weapon_timer = nullptr;
};

#endif // ENEMYWEAPON_H
