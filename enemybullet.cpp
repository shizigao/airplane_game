#include "enemybullet.h"

EnemyBullet::EnemyBullet()
{

}

EnemyBullet::EnemyBullet(double x, double y, QPixmap pixmap)
{
    setPixmap(pixmap);
    setPos(x, y);
    rect.setSize(QSize(pixmap.width(), pixmap.height()));//设置子弹的矩形碰撞箱
}

void EnemyBullet::init(double x, double y, int kind)
{
    bullet_kind = kind;
    setPos(x, y);
    setVisible(true);
    status = 2;
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

void EnemyBullet::init_1()
{
    setPixmap(QPixmap(ENEMYBULLET_PICTURE1));
}

void EnemyBullet::init_2()
{

}

void EnemyBullet::init_3()
{

}

void EnemyBullet::init_4()
{

}

void EnemyBullet::destroy()
{
    setVisible(false);
}

void EnemyBullet::move()
{
    switch(bullet_kind){
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

void EnemyBullet::move_1()
{
    double x = pos().x(), y = pos().y();
    y += speed;
    setPos(x, y);
}

void EnemyBullet::move_2()
{

}

void EnemyBullet::move_3()
{

}

void EnemyBullet::move_4()
{

}

void EnemyBullet::is_live()
{
    //检测子弹是否出界
    double x = pos().x(), y = pos().y();
    if ((y >= 1200 || x <= -100 || x >= 900) && status == 2){
        status = 0;
        destroy();
    }
}

void EnemyBullet::set_value(EnemyWeapon *enemyweapon)
{
    damage = enemyweapon->damage;
    speed = enemyweapon->speed;
}
