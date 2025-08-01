#include "enemyweapon.h"

EnemyWeapon::EnemyWeapon()
{
    weapon_timer = new QTimer();
}

void EnemyWeapon::init(int weapon_kind)
{
    this->weapon_kind = weapon_kind;
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

void EnemyWeapon::init1()
{
    interval = ENEMYWEAPON1_INTERVAL;
    speed = ENEMYWEAPON1_SPEED;

    weapon_timer->setInterval(interval);
    weapon_timer->setSingleShot(true);
    weapon_timer->start();
}

void EnemyWeapon::init2()
{
    
}

void EnemyWeapon::init3()
{
    
}

void EnemyWeapon::init4()
{
    
}
