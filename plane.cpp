#include "plane.h"

Plane::Plane()
{

}

Plane::Plane(int x, int y, QPixmap pixmap)
{
    setPixmap(pixmap);
    setPos(x, y);
    rect.setSize(QSize(pixmap.width(), pixmap.height()));//设置飞机的矩形碰撞箱
}
