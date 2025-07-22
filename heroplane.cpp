#include "heroplane.h"

HeroPlane::HeroPlane()
{

}

HeroPlane::HeroPlane(double x, double y, QPixmap pixmap)
{
    setPos(x, y);
    setPixmap(pixmap);
    rect.setSize(QSize(pixmap.width(), pixmap.height()));//设置飞机的矩形碰撞箱
    speed = 10;
}

void HeroPlane::move_to(double x, double y)
{
    if (x <= 0)x = 0;
    if (x >= VIEW_WIDTH - 100)x = VIEW_WIDTH - 100;
    if (y >= VIEW_HEIGHT - 65)y = VIEW_HEIGHT - 65;
    if (y <= 0)y = 0;
    setPos(x, y);
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
