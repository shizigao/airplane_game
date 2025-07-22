#include "heroweapon.h"

HeroWeapon::HeroWeapon()
{
}

void HeroWeapon::init(int kind)
{
    weapon_kind = kind;
    switch(kind){
    case 1:
        init_1();
        break;
    case 2:
        init_2();
        break;
    case 3:
        init_3();
        break;
    case 4:
        init_4();
        break;
    }
}

void HeroWeapon::init_1()
{
    damage = HEROWEAPON1_DAMAGE;
    interval = HEROWEAPON1_INTERVAL;
    speed = HEROWEAPON1_SPEED;
    setPixmap(QPixmap(WEAPON_PICTURE1));
}

void HeroWeapon::init_2()
{

}

void HeroWeapon::init_3()
{

}

void HeroWeapon::init_4()
{

}
