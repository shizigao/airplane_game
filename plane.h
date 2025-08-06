#ifndef PLANE_H
#define PLANE_H
#include <QGraphicsPixmapItem>
#include "config.h"

class Plane:public QGraphicsPixmapItem
{
public:
    Plane();
    //获取剩余生命的百分比
    double get_health_rate();

public:
    //飞机的速度
    double speed = 0;
    //状态
    int status = 0;//0:失效态, 1:等待态, 2:激活态
    //当前生命
    double health = 0;
    //最大生命
    double max_health = 0;
    //碰撞伤害
    double damage = 0;

};

#endif // PLANE_H
