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
    //状态
    int status = 0;//0表示不可用（已死亡），1表示已进入对象池未使用，2表示正在使用（存活），用于对象池逻辑





};

#endif // PLANE_H
