#include "enemybullet.h"

EnemyBullet::EnemyBullet()
{

}

void EnemyBullet::init(int bullet_kind, EnemyWeapon *enemyweapon)
{
    this->bullet_kind = bullet_kind;
    switch(bullet_kind){
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
    //把武器的数值赋值给子弹
    speed = enemyweapon->speed;
}

void EnemyBullet::init1()
{
    setPixmap(QPixmap(ENEMYBULLET1_PICTURE));
}

void EnemyBullet::init2()
{

}

void EnemyBullet::init3()
{

}

void EnemyBullet::init4()
{

}

void EnemyBullet::move()
{
    switch(bullet_kind){
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

    //判断子弹是否超出边界
    double x = pos().x(), y = pos().y();
    if (x < -100 || x > GAME_WIDTH + 100 || y < -100 || y > GAME_HEIGHT + 100){
        destroy();
    }
}

void EnemyBullet::move1()
{
    //直线移动
    moveBy(0, speed);
}

void EnemyBullet::move2()
{

}

void EnemyBullet::move3()
{

}

void EnemyBullet::move4()
{

}

void EnemyBullet::destroy()
{
    status = 0;
    setVisible(false);//设置图片不可见
}
