#include "heroplane.h"

HeroPlane::HeroPlane()
{

}

HeroPlane::HeroPlane(int x, int y, QPixmap pixmap)
{
    setPos(x, y);
    setPixmap(pixmap);
    rect.setSize(QSize(pixmap.width(), pixmap.height()));//设置飞机的矩形碰撞箱
}
