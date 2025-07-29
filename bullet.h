#ifndef BULLET_H
#define BULLET_H
#include "config.h"
class Bullet: public QGraphicsPixmapItem
{
public:
    Bullet();
public:
    //状态
    int status = 0;//0:失效态, 1:等待态, 2:激活态

    //子弹移动速度
    double speed = 0;
};

#endif // BULLET_H
