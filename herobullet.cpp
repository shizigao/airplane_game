#include "herobullet.h"
#include "enemyplane.h"
HeroBullet::HeroBullet()
{

}


void HeroBullet::init(double x, double y, int kind)
{
    bullet_kind = kind;
    setPos(x, y);
    setVisible(true);
    status = 2;
    switch (kind) {
    case 1:
        init_1();
        break;
    case 2:
        init_2();
        break;
    case 3:
        init_3();
        break;
    case 4:
        init_4();
        break;
    default:
        break;
    }

}

void HeroBullet::init_1()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE1));
}

void HeroBullet::init_2()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE2));

    amplitude = 30.0;   // 摆动幅度
    frequency = 0.3;   // 摆动频率
}

void HeroBullet::init_3()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE3));
}

void HeroBullet::init_4()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE4));
}

void HeroBullet::destroy()
{
    status = 0;
    setVisible(false);
}

void HeroBullet::move(QList<EnemyPlane*>& enemyplane_pool)
{
    switch(bullet_kind){
    case 1:
        move_1();
        break;

    case 2:
        move_2();
        break;

    case 3:
        move_3();
        break;

    case 4:
        move_4(enemyplane_pool);
        break;
    }
}

void HeroBullet::move_1()
{
    double x = pos().x(), y = pos().y();
    y -= speed;
    setPos(x, y);
}

void HeroBullet::move_2()
{
    // 基础向前移动（假设向上飞行，y轴递减）
       setY(y() - speed);  // speed是子弹的基础速度，需在类中定义或通过set_value设置

       // 曲线偏移计算：使用正弦函数实现横向摆动
       static double angle = 0;  // 角度变量，用于计算正弦值
       double offsetX = amplitude * sin(angle);  // amplitude是摆动幅度

       // 更新x坐标（加入横向偏移）
       setX(x() + offsetX);

       // 每次调用增加角度，控制摆动频率
       angle += frequency;  // frequency是摆动频率，值越大摆动越快

       // 防止角度过大导致精度问题，重置角度
       if (angle >= 2 * M_PI) {
           angle = 0;
       }
}

void HeroBullet::move_3()
{
    double x = pos().x(), y = pos().y();
    y -= speed;
    setPos(x, y);
}

void HeroBullet::move_4(QList<EnemyPlane*>& enemyplane_pool)
{
    //子弹自身的坐标
    double x = pos().x(), y = pos().y();

    EnemyPlane* nearest_enemyplane = nullptr;//最近的敌机
    //遍历敌机池，找到最近的敌机
    double nearest_distance = 1000000;
    for (EnemyPlane* enemyplane : enemyplane_pool){
        if (enemyplane->status != 2)continue;
        double px = enemyplane->pos().x(), py = enemyplane->pos().y();
        double dx = x - px, dy = y - py;
        double distance = sqrt(dx * dx + dy * dy);
        if (distance < nearest_distance){
            nearest_distance = distance;
            nearest_enemyplane = enemyplane;
        }
    }
    if (nearest_enemyplane){//找到敌机
        double dx = nearest_enemyplane->pos().x() - x, dy = nearest_enemyplane->pos().y() - y;
        x += (dx / nearest_distance) * speed;
        y += (dy / nearest_distance) * speed;
    }
    else{//未找到敌机
        y -= speed;
    }
    setPos(x, y);
}

void HeroBullet::is_live()
{
    //检测子弹是否出界
    double x = pos().x(), y = pos().y();
    if ((y <= -100 || x <= -100 || x >= 900) && status == 2){
        destroy();
    }
}

void HeroBullet::set_value(HeroWeapon *heroweapon)
{
    damage = heroweapon->damage;
    speed = heroweapon->speed;
}

void HeroBullet::collide_with_enemyplane(EnemyPlane *enemyplane)
{
    //碰撞后根据设计，判断子弹是否失效（如果为穿透弹则不失效）
    switch(bullet_kind){
    case 1:
        destroy();
        break;
    case 2:
        destroy();
        break;
    case 3:
        break;
    case 4:
        destroy();
    }
}
