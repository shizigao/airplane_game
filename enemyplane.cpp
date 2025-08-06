#include "enemyplane.h"
#include "heroplane.h"
EnemyPlane::EnemyPlane()
{
    weapon = new EnemyWeapon();
}

void EnemyPlane::init(int plane_kind)
{
    this->plane_kind = plane_kind;
    switch(plane_kind){
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

void EnemyPlane::init1()
{
    setPixmap(QPixmap(ENEMYPLANE1_PICTURE));
    speed = ENEMYPLANE1_SPEED;
    health = ENEMYPLANE1_HEALTH;
    damage = ENEMYPLANE1_DAMAGE;
    weapon->init(1);
}

void EnemyPlane::init2()
{

}

void EnemyPlane::init3()
{

}

void EnemyPlane::init4()
{

}

void EnemyPlane::move()
{
    switch(plane_kind){
    case 1:
        move1();
        break;
    case 2:
        move2();
        break;
    case 3:
        move3();
        break;
    case 4:
        move4();
        break;

    }

    //判断敌机是否超出边界
    double x = pos().x(), y = pos().y();
    if (x < -100 || x > GAME_WIDTH + 100 || y < -100 || y > GAME_HEIGHT + 100){
        destroy();
    }
}

void EnemyPlane::move1()
{
   //直线移动
    moveBy(0, speed);
}

void EnemyPlane::move2()
{

}

void EnemyPlane::move3()
{

}

void EnemyPlane::move4()
{

}

void EnemyPlane::weapon_shoot(EnemyBulletPool *enemybullet_pool, QGraphicsScene *level_scene)
{
    if (!weapon || weapon->weapon_timer->isActive())return;
    EnemyBullet* enemybullet = enemybullet_pool->get_new_enemybullet();
    enemybullet->init(weapon->weapon_kind, weapon);
    enemybullet->setPos(pos().x() + pixmap().width() / 2.0 - 8, pos().y() + 18);
    //重新计时
    weapon->weapon_timer->start();
}

void EnemyPlane::destroy()
{
    weapon->weapon_timer->stop();
    status = 0;
    setVisible(false);
}

void EnemyPlane::collide_with_herobullet(HeroBullet *herobullet)
{
    switch(herobullet->bullet_kind){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    health -= herobullet->damage;

}

void EnemyPlane::collide_with_heroplane(HeroPlane *heroplane)
{
    switch(heroplane->plane_kind){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }

    health -= heroplane->damage;

}

void EnemyPlane::is_live()
{
    if (health <= 0){
        destroy();
    }
}
