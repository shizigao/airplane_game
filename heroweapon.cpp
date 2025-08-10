#include "heroweapon.h"

HeroWeapon::HeroWeapon()
{

}

HeroWeapon::~HeroWeapon()
{
    weapon_timer->stop();
    delete weapon_timer;
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
    weapon_timer->setInterval(interval);
    weapon_timer->setSingleShot(true);
    weapon_timer->start();
}

void HeroWeapon::init1()
{
    interval = HEROWEAPON1_INTERVAL;
    speed = HEROWEAPON1_SPEED;
    damage = HEROWEAPON1_DAMAGE;



}

void HeroWeapon::init2()
{
    interval = HEROWEAPON2_INTERVAL;
    speed = HEROWEAPON2_SPEED;
    damage = HEROWEAPON2_DAMAGE;

}

void HeroWeapon::init3()
{
    interval = HEROWEAPON3_INTERVAL;
    speed = HEROWEAPON3_SPEED;
    damage = HEROWEAPON3_DAMAGE;
}

void HeroWeapon::init4()
{
    interval = HEROWEAPON4_INTERVAL;
    speed = HEROWEAPON4_SPEED;
    damage = HEROWEAPON4_DAMAGE;
}

