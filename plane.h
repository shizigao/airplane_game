#ifndef PLANE_H
#define PLANE_H
#include "config.h"

class Plane: public QGraphicsPixmapItem
{
public:
    Plane();
    Plane(double x, double y, QPixmap pixmap);

public:
    //坐标由父类自带的pos控制
    //移动速度
    double speed = 5;
    //生命值
    double health = 100;
    //矩形碰撞箱
    QRect rect;
    //状态
    int status = 0;//0表示不可用（已死亡），1表示已进入对象池未使用，2表示正在使用（存活），用于对象池逻辑
    //子弹伤害
    double damage = 10;
    //子弹发射间隔
    double fire_interval = 1000;//单位:ms





};

#endif // PLANE_H
