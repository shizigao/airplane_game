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
    case 5:
        init_boss1();
        break;
    case 6:
        init_boss2();
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
    damage = ENEMYWEAPON2_DAMAGE;
    interval = ENEMYWEAPON2_INTERVAL;
    speed = ENEMYWEAPON2_SPEED;
    setPixmap(QPixmap(ENEMYBULLET_PICTURE2));
}

void EnemyWeapon::init_3()
{
    damage = ENEMYWEAPON3_DAMAGE;
    interval = ENEMYWEAPON3_INTERVAL;
    speed = ENEMYWEAPON3_SPEED;
    setPixmap(QPixmap(ENEMYBULLET_PICTURE3));
}

void EnemyWeapon::init_4()
{
    damage = ENEMYWEAPON4_DAMAGE;
    interval = ENEMYWEAPON4_INTERVAL;
    speed = ENEMYWEAPON4_SPEED;
    setPixmap(QPixmap(ENEMYBULLET_PICTURE4));
}

void EnemyWeapon::init_boss1()
{
    damage = BOSSWEAPON1_DAMAGE;
    interval = BOSSWEAPON1_INTERVAL;
    speed = BOSSWEAPON1_SPEED;
    setPixmap(QPixmap(BOSS_BULLET_PICTURE1));
}

void EnemyWeapon::init_boss2()
{
    damage = BOSSWEAPON2_DAMAGE;
    interval = BOSSWEAPON2_INTERVAL;
    speed = BOSSWEAPON2_SPEED;
    setPixmap(QPixmap(BOSS_BULLET_PICTURE2));
}
