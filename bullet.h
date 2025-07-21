#ifndef BULLET_H
#define BULLET_H
#include "config.h"

class Bullet: public QGraphicsPixmapItem
{
public:
    Bullet();
    Bullet(int x, int y, QPixmap pixmap);

    //矩形碰撞箱
    QRect rect;

    //状态
    int status = 0;//0表示不可用（已死亡），1表示已进入对象池未使用，2表示正在使用（存活），用于对象池逻辑

};

#endif // BULLET_H
