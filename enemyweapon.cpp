#include "enemyweapon.h"

EnemyWeapon::EnemyWeapon()
{

}

void EnemyWeapon::init(int kind)
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

void EnemyWeapon::init_1()
{
    damage = ENEMYWEAPON1_DAMAGE;
    interval = ENEMYWEAPON1_INTERVAL;
    speed = ENEMYWEAPON1_SPEED;
    setPixmap(QPixmap(ENEMYBULLET_PICTURE1));
}

void EnemyWeapon::init_2()
{

}

void EnemyWeapon::init_3()
{

}

void EnemyWeapon::init_4()
{

}
