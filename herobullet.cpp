#include "herobullet.h"

HeroBullet::HeroBullet()
{

}

HeroBullet::HeroBullet(double x, double y, QPixmap pixmap)
{
    setPixmap(pixmap);
    setPos(x, y);
    rect.setSize(QSize(pixmap.width(), pixmap.height()));//设置子弹的矩形碰撞箱
}

void HeroBullet::init(double x, double y, int kind)
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

void HeroBullet::init_1()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE1));
}

void HeroBullet::init_2()
{

}

void HeroBullet::init_3()
{

}

void HeroBullet::init_4()
{

}

void HeroBullet::destroy()
{
    setVisible(false);
}

void HeroBullet::move()
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

void HeroBullet::move_1()
{
    double x = pos().x(), y = pos().y();
    y -= speed;
    setPos(x, y);
}

void HeroBullet::move_2()
{

}

void HeroBullet::move_3()
{

}

void HeroBullet::move_4()
{

}

void HeroBullet::is_live()
{
    //检测子弹是否出界
    double x = pos().x(), y = pos().y();
    if ((y <= -100 || x <= -100 || x >= 900) && status == 2){
        status = 0;
        destroy();
    }
}

void HeroBullet::set_value(HeroWeapon *heroweapon)
{
    damage = heroweapon->damage;
    speed = heroweapon->speed;
}
