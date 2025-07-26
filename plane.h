#ifndef PLANE_H
#define PLANE_H
#include "config.h"

class Plane: public QGraphicsPixmapItem
{
public:
    Plane();

public:
    //坐标由父类自带的pos控制
    //移动速度
    double speed = 5;
    //生命值
    double max_health = 100;//最大生命值
    double health = 100;//即时生命值

    //状态
    int status = 0;//0表示不可用（已死亡），1表示已进入对象池未使用，2表示正在使用（存活），用于对象池逻辑
    //撞击伤害
    int damage = 10;





};

#endif // PLANE_H
