#ifndef ENEMYWEAPON_H
#define ENEMYWEAPON_H
#include "weapon.h"

class EnemyWeapon: public Weapon
{
public:
    EnemyWeapon();

    //武器初始化
    void init(int kind);
    void init_1();//第一种武器初始化
    void init_2();//第二种武器初始化
    void init_3();//第三种武器初始化
    void init_4();//第四种武器初始化
    void init_boss1();//第三种武器初始化
    void init_boss2();//第四种武器初始化


public:
    //敌机武器的种类（和敌机、敌机子弹一一对应）
    int weapon_kind = 1;
};

#endif // ENEMYWEAPON_H
