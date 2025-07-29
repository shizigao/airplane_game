#include "heroplane.h"
HeroPlane::HeroPlane()
{

}

void HeroPlane::init(int heroplane_kind)
{
    this->heroplane_kind = heroplane_kind;
    switch(heroplane_kind){
    case 1:
        init_1();
        break;
    case 2:
        init_2();
        break;
    }
}

void HeroPlane::init_1()
{
    speed = HEROPLANE1_SPEED;
    setPixmap(QPixmap(HEROPLANE1_PICTURE));
    weapon1 = new HeroWeapon();
    weapon1->init(1);
}

void HeroPlane::init_2()
{
    speed = HEROPLANE2_SPEED;
    setPixmap(QPixmap(HEROPLANE2_PICTURE));

}

void HeroPlane::weapon1_shoot(HeroBulletPool* herobullet_pool, QGraphicsScene* level_scene)
{
    if (!weapon1 || weapon1->weapon_timer->isActive())return;
    HeroBullet* herobullet = herobullet_pool->get_new_herobullet();
    herobullet->init(weapon1->weapon_kind);
    herobullet->setPos(pos().x() + pixmap().width() / 2.0 - 8, pos().y() - 18);
    //重新计时
    weapon1->weapon_timer->start();
}

void HeroPlane::weapon2_shoot(HeroBulletPool *herobullet_pool, QGraphicsScene *level_scene)
{
    if (!weapon2 || weapon2->weapon_timer->isActive())return;
    HeroBullet* herobullet = herobullet_pool->get_new_herobullet();
    herobullet->init(weapon2->weapon_kind);
    herobullet->setPos(pos().x(), pos().y());
    //重新计时
    weapon2->weapon_timer->start();
}

void HeroPlane::weapon3_shoot(HeroBulletPool *herobullet_pool, QGraphicsScene *level_scene)
{
    if (!weapon3 || weapon3->weapon_timer->isActive())return;
    HeroBullet* herobullet = herobullet_pool->get_new_herobullet();
    herobullet->init(weapon3->weapon_kind);
    herobullet->setPos(pos().x(), pos().y());
    //重新计时
    weapon3->weapon_timer->start();
}
