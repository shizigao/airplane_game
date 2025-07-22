#ifndef HEROWEAPON_H
#define HEROWEAPON_H
#include "Weapon.h"

class HeroWeapon: public Weapon
{
public:
    HeroWeapon();

    //武器初始化
    void init(int kind);
    void init_1();//第一种武器初始化
    void init_2();//第二种武器初始化
    void init_3();//第三种武器初始化
    void init_4();//第四种武器初始化

public:
    //英雄机武器的种类（和子弹一一对应）
    int weapon_kind = 1;

};

#endif // HEROWEAPON_H
