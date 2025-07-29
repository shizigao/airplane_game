#ifndef PLANE_H
#define PLANE_H
#include <QGraphicsPixmapItem>
#include "config.h"

class Plane:public QGraphicsPixmapItem
{
public:
    Plane();

public:
    //飞机的速度
    double speed = 0;
    //状态
    int status = 0;//0:失效态, 1:等待态, 2:激活态

};

#endif // PLANE_H
