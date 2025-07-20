#ifndef PLANE_H
#define PLANE_H
#include "config.h"

class Plane: public QGraphicsPixmapItem
{
public:
    Plane();
    Plane(int x, int y, QPixmap pixmap);

public:
    //坐标由父类自带的pos控制
    //移动速度
    int speed = 5;
    //生命值
    int health = 100;
    //矩形碰撞箱
    QRect rect;






};

#endif // PLANE_H
