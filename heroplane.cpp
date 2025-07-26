#include "heroplane.h"

HeroPlane::HeroPlane(QTimer* invincible_timer)
{
    this->invincible_timer = invincible_timer;
    shield = new QGraphicsPixmapItem();
    shield->setVisible(false);
    shield->setScale(0.4);
    shield->setOpacity(0.4);//设置透明度
    shield->setPos(-12, -22);//设置相对坐标
    shield->setPixmap(QPixmap(SHIELD_PICTURE));
    shield->setParentItem(this);//将护盾与飞机绑定在一起

    level_up_text = new QGraphicsPixmapItem();
    level_up_text->setParentItem(this);//将升级文字与飞机绑定在一起
    level_up_text->setVisible(false);
    level_up_text->setPos(0, -40); // 显示在飞机上方
    level_up_text->setPixmap(QPixmap(UPGRADE_PICTURE));
}

HeroPlane::~HeroPlane()
{
    if(weapon1 != nullptr)
        delete weapon1;
    if (weapon2 != nullptr)
        delete weapon2;
    if (weapon3 != nullptr)
        delete weapon3;
    if (invincible_timer){
        invincible_timer->stop();
    }
}



void HeroPlane::move_to(double x, double y)
{
    if (x <= 0)x = 0;
    if (x >= VIEW_WIDTH - 100)x = VIEW_WIDTH - 100;
    if (y >= VIEW_HEIGHT - 65)y = VIEW_HEIGHT - 65;
    if (y <= 0)y = 0;
    setPos(x, y);
}

void HeroPlane::init(double x, double y, int kind)
{
    setPos(x, y);
    setVisible(true);
    status = 2;
    plane_kind = kind;
    experience = 0;
    level = 1;
    rate_sum = 1;
    next_level_experience = UPGRADE_EXPERIENCE;
    switch(kind){
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

void HeroPlane::init1()
{
    setPixmap(QPixmap(HEROPLANE_1_PICTURE));
    max_health = HEROPLANE1_HEALTH;
    health = max_health;
    damage = HEROPLANE1_DAMAGE;
    speed = HEROPLANE1_SPEED;
    setVisible(true);
}

void HeroPlane::init2()
{
    setPixmap(QPixmap(HEROPLANE_2_PICTURE));
    max_health = HEROPLANE2_HEALTH;
    health = max_health;
    damage = HEROPLANE2_DAMAGE;
    speed = HEROPLANE2_SPEED;
    setVisible(true);
}

void HeroPlane::init3()
{

}

void HeroPlane::init4()
{

}

void HeroPlane::weapon1_shoot()
{

}

void HeroPlane::weapon2_shoot()
{

}

void HeroPlane::weapon3_shoot()
{

}

void HeroPlane::collide_with_enemybullet(EnemyBullet *enemybullet)
{
    health -= enemybullet->damage;
    invincible_timer->start(INVINCIBLE_TIME);//1000ms的无敌时间
    shield->setVisible(true);
}

void HeroPlane::collide_with_enemyplane(EnemyPlane *enemyplane)
{
    health -= enemyplane->damage;
    invincible_timer->start(INVINCIBLE_TIME);//1000ms的无敌时间
    shield->setVisible(true);
}

void HeroPlane::is_live()
{
    if (health <= 0){//如果生命值小于0则死亡
        status = 0;
    }
}

bool HeroPlane::is_upgrade()
{
    if (experience >= next_level_experience){
        upgrade();
        return true;
    }
    return false;
}

void HeroPlane::upgrade()
{
    level++;
    rate_sum *= UPGRADE_RATE;
    max_health *= UPGRADE_RATE;
    health = max_health;
    damage *= UPGRADE_RATE;
    next_level_experience *= 1 + (UPGRADE_RATE - 1) * 2;
    experience = 0;//经验值清零


    if (level == 2){
        while(!weapon2){//随机抽出一个武器作为第二个武器
            int num = (rand() % 4) + 1;//num是武器种类的编号
            if (num != weapon1->weapon_kind){//不能抽得一样
                weapon2 = new HeroWeapon();
                weapon2->init(num);//初始化
                weapon2->setZValue(-1);
            }
        }
    }
    else if (level == 3){
        while(!weapon3){//随机抽出一个武器作为第三个武器
            int num = (rand() % 4) + 1;//num是武器种类的编号
            if (num != weapon1->weapon_kind && num != weapon2->weapon_kind){//不能抽得一样
                weapon3 = new HeroWeapon();
                weapon3->init(num);//初始化
                weapon3->setZValue(-1);
            }
        }
    }
    else{//第三级以后就是武器等级的提升
        int num = (rand() % 3) + 1;
        if (num == 1){
            weapon1->upgrade();
        }
        if (num == 2){
            weapon2->upgrade();
        }
        if (num == 3){
            weapon3->upgrade();
        }
    }
}
