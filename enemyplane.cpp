#include "enemyplane.h"


void EnemyPlane::init(double x, double y, int kind)
{
    this->setVisible(true);
    status = 2;
    setPos(x, y);
    this->plane_kind = kind;
    switch (kind) {
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
    default:
        break;
    }
}

EnemyPlane::EnemyPlane(QTimer *weapon_timer)
{
    this->weapon_timer = weapon_timer;
}

void EnemyPlane::init_1()
{
    setPixmap(QPixmap(ENEMYPLANE_PICTURE1));
    speed = 2;
    //对应第一种武器
    weapon = new EnemyWeapon();
    weapon->init(1);

    weapon_timer->start(weapon->interval);
}

void EnemyPlane::init_2()
{

}

void EnemyPlane::init_3()
{

}

void EnemyPlane::init_4()
{

}

void EnemyPlane::destroy()
{
    setVisible(false);
}

void EnemyPlane::move()
{
    switch(plane_kind){
    case 1:
        move_1();
        break;

    case 2:
        move_2();
        break;

    case 3:
        move_3();
        break;

    case 4:
        move_4();
        break;
    }
}

void EnemyPlane::move_1()
{
    double y = pos().y(), x = pos().x();
    y += speed;
    setPos(x, y);
}

void EnemyPlane::move_2()
{

}

void EnemyPlane::move_3()
{

}

void EnemyPlane::move_4()
{

}



void EnemyPlane::is_live()
{
    double x = pos().x(), y = pos().y();
    //超过边界则死亡
    if (y >= 1200 && status == 2){
        status = 0;
        destroy();
    }
    //生命值降为负数则死亡
}
