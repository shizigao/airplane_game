#include "enemyplane.h"
EnemyPlane::EnemyPlane()
{

}

void EnemyPlane::init(int plane_kind)
{
    this->plane_kind = plane_kind;
    switch(plane_kind){
    case 1:
        init1();
        break;
    case 2:
        init2();
        break;
    case 3:
        init3();
        break;
    case 4:
        init4();
        break;
    }
}

void EnemyPlane::init1()
{
    setPixmap(QPixmap(ENEMYPLANE1_PICTURE));
    speed = ENEMYPLANE1_SPEED;
}

void EnemyPlane::init2()
{

}

void EnemyPlane::init3()
{

}

void EnemyPlane::init4()
{

}

void EnemyPlane::move()
{
    switch(plane_kind){
    case 1:
        move1();
        break;
    case 2:
        move2();
        break;
    case 3:
        move3();
        break;
    case 4:
        move4();
        break;

    }

    //判断敌机是否超出边界
    double x = pos().x(), y = pos().y();
    if (x < -100 || x > GAME_WIDTH + 100 || y < -100 || y > GAME_HEIGHT + 100){
        destroy();
    }
}

void EnemyPlane::move1()
{
   //直线移动
    moveBy(0, speed);
}

void EnemyPlane::move2()
{

}

void EnemyPlane::move3()
{

}

void EnemyPlane::move4()
{

}

void EnemyPlane::destroy()
{
    status = 0;
    setVisible(false);
}
