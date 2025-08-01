#include "heroweapon.h"

HeroWeapon::HeroWeapon()
{

}

void HeroWeapon::init(int weapon_kind)
{
    this->weapon_kind = weapon_kind;
    weapon_timer = new QTimer();
    switch(weapon_kind){
    case 1:
        init1();
        break;
    case 2:
        init2();
        break;
    case 3:
        init3();
        break;
    case 4:
        init4();
        break;
    }
}

void HeroWeapon::init1()
{
    interval = HEROWEAPON1_INTERVAL;
    speed = HEROWEAPON1_SPEED;
    damage = HEROWEAPON1_DAMAGE;

    weapon_timer->setInterval(interval);
    weapon_timer->setSingleShot(true);
    weapon_timer->start();

}

void HeroWeapon::init2()
{

}

void HeroWeapon::init3()
{

}

void HeroWeapon::init4()
{

}
