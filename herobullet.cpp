#include "herobullet.h"

HeroBullet::HeroBullet()
{

}

HeroBullet::HeroBullet(int x, int y, QPixmap pixmap)
{
    setPixmap(pixmap);
    setPos(x, y);
    rect.setSize(QSize(pixmap.width(), pixmap.height()));//设置子弹的矩形碰撞箱
}
