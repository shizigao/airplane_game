#include "heroweapon.h"

HeroWeapon::HeroWeapon()
{
}

void HeroWeapon::init(int kind)
{
    weapon_kind = kind;
    weapon_level = 1;
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
    damage = HEROWEAPON2_DAMAGE;
    interval = HEROWEAPON2_INTERVAL;
    speed = HEROWEAPON2_SPEED;
    setPixmap(QPixmap(WEAPON_PICTURE2));
}

void HeroWeapon::init_3()
{
    damage = HEROWEAPON3_DAMAGE;
    interval = HEROWEAPON3_INTERVAL;
    speed = HEROWEAPON3_SPEED;
    setPixmap(QPixmap(WEAPON_PICTURE3));
}

void HeroWeapon::init_4()
{
    damage = HEROWEAPON4_DAMAGE;
    interval = HEROWEAPON4_INTERVAL;
    speed = HEROWEAPON4_SPEED;
    setPixmap(QPixmap(WEAPON_PICTURE4));
}

void HeroWeapon::upgrade()
{
    damage *= UPGRADE_RATE * 3;
    qDebug() << "weapon" << weapon_kind << "level" << weapon_level << "damage" << damage;
    weapon_level++;
}

