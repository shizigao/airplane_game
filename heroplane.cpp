#include "heroplane.h"
HeroPlane::HeroPlane()
{

}

HeroPlane::~HeroPlane()
{
    if (weapon1) delete weapon1;
    if (weapon2) delete weapon2;
    if (weapon3) delete weapon3;
    shield_timer->stop();
    delete shield_timer;
}

void HeroPlane::init(int heroplane_kind)
{
    this->plane_kind = heroplane_kind;
    //护盾
    shield = new QGraphicsPixmapItem();
    shield->setParentItem(this);
    shield->setPixmap(QPixmap(SHIELD_PICTURE));
    shield->setScale(0.3);
    shield->setOpacity(0.5);
    shield->setPos(-4, -12);
    shield->setVisible(false);

    shield_timer = new QTimer();
    shield_timer->setSingleShot(true);

    //升级图片
    upgrade_picture = new QGraphicsPixmapItem();
    upgrade_picture->setParentItem(this);
    upgrade_picture->setPixmap(QPixmap(UPGRADE_PICTURE));
    upgrade_picture->setPos(0, -40);
    upgrade_picture->setVisible(false);



    status = 2;//状态设置为2
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
    max_health = HEROPLANE1_HEALTH;
    health = max_health;
    damage = HEROPLANE1_DAMAGE;
    setPixmap(QPixmap(HEROPLANE1_PICTURE));
    weapon1 = new HeroWeapon();
    weapon1->init(4);
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
    herobullet->init(weapon1->weapon_kind, weapon1);
    herobullet->setPos(pos().x() + pixmap().width() / 2.0 - 8, pos().y() - 18);
    //重新计时
    weapon1->weapon_timer->start();
}

void HeroPlane::weapon2_shoot(HeroBulletPool *herobullet_pool, QGraphicsScene *level_scene)
{
    if (!weapon2 || weapon2->weapon_timer->isActive())return;
    HeroBullet* herobullet = herobullet_pool->get_new_herobullet();
    herobullet->init(weapon2->weapon_kind, weapon2);
    herobullet->setPos(pos().x(), pos().y());
    //重新计时
    weapon2->weapon_timer->start();
}

void HeroPlane::weapon3_shoot(HeroBulletPool *herobullet_pool, QGraphicsScene *level_scene)
{
    if (!weapon3 || weapon3->weapon_timer->isActive())return;
    HeroBullet* herobullet = herobullet_pool->get_new_herobullet();
    herobullet->init(weapon3->weapon_kind, weapon3);
    herobullet->setPos(pos().x(), pos().y());
    //重新计时
    weapon3->weapon_timer->start();
}

void HeroPlane::collide_with_enemybullet(EnemyBullet *enemybullet)
{
    switch(enemybullet->bullet_kind){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    if (shield_timer->isActive())return;
    health -= enemybullet->damage;
    shield_timer->setInterval(SHIELD_PERIOD_1);
    shield_timer->start();
}

void HeroPlane::collide_with_enemyplane(EnemyPlane *enemyplane)
{
    switch(enemyplane->plane_kind){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    if (shield_timer->isActive())return;
    health -= enemyplane->damage;
    shield_timer->setInterval(SHIELD_PERIOD_1);
    shield_timer->start();
}

void HeroPlane::upgrade(QWidget* widget)
{
    //显示升级画面
    QTimer* timer = new QTimer();
    timer->setSingleShot(true);
    widget->connect(timer, QTimer::timeout, widget, [=](){
        upgrade_picture->setVisible(false);
        widget->disconnect(timer, nullptr, nullptr, nullptr);
        delete timer;
    });
    upgrade_picture->setVisible(true);
    timer->start(1000);//显示1000ms

    experience = 0;
    next_level_experience *= UPGRADE_EXPERIENCE_INCREASE_RATE;//每升一级，所需经验值增长

    //属性提升
    max_health *= UPGRADE_VALUE_RATE;
    damage *= UPGRADE_VALUE_RATE;
    health = max_health;

}

int HeroPlane::get_experience_rate()
{
    return experience / (double)next_level_experience * 100;
}
