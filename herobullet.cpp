#include "herobullet.h"

HeroBullet::HeroBullet()
{

}

void HeroBullet::init(int bullet_kind, HeroWeapon* heroweapon)
{
    this->bullet_kind = bullet_kind;
    switch(bullet_kind){
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
    //把武器的数值赋值给子弹
    speed = heroweapon->speed;
    damage = heroweapon->damage;
}

void HeroBullet::init1()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE1));
}

void HeroBullet::init2()
{

}

void HeroBullet::init3()
{

}

void HeroBullet::init4()
{

}

void HeroBullet::move()
{
    switch(bullet_kind){
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

    //判断子弹是否超出边界
    double x = pos().x(), y = pos().y();
    if (x < -100 || x > GAME_WIDTH + 100 || y < -100 || y > GAME_HEIGHT + 100){
        destroy();
    }
}

void HeroBullet::move1()
{
    moveBy(0, -speed);//直线向上移动
}

void HeroBullet::move2()
{

}

void HeroBullet::move3()
{

}

void HeroBullet::move4()
{

}

void HeroBullet::destroy()
{
    status = 0;
    setVisible(false);//设置图片不可见
}

void HeroBullet::collide_with_enemyplane()
{
    switch(bullet_kind){
    case 1:
        destroy();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
}
