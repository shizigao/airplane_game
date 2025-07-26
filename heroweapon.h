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
    //1是正常子弹，2是正弦函数移动的子弹，3是穿甲弹，4是追踪弹

    //武器的升级
    void upgrade();

public:
    //英雄机武器的种类（和子弹一一对应）
    int weapon_kind = 1;
    int weapon_level = 1;//武器的等级
};

#endif // HEROWEAPON_H
