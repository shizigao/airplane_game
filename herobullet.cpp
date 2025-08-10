#include "herobullet.h"
#include "enemyplane.h"
#include <cmath>
#include <QtMath>

HeroBullet::HeroBullet()
{

}

void HeroBullet::init(int bullet_kind, HeroWeapon* heroweapon)
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
    speed = heroweapon->speed;
    damage = heroweapon->damage;
}

void HeroBullet::init1()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE1));
}

void HeroBullet::init2()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE2));
}

void HeroBullet::init3()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE3));
}

void HeroBullet::init4()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE4));


}

void HeroBullet::move(EnemyPlanePool* enemyplane_pool)
{
    switch(bullet_kind){
    case 1:
        move1();
        break;
    case 2:
        move2();
        break;
    case 3:
        move3(enemyplane_pool);
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

void HeroBullet::move1()
{
    moveBy(0, -speed);//直线向上移动
}

void HeroBullet::move2()
{
    moveBy(0, -speed);//直线向上移动
}

void HeroBullet::move3(EnemyPlanePool* enemyplane_pool)
{
    // 子弹自身的坐标
    double x = pos().x();
    double y = pos().y();
    EnemyPlane* nearest_enemyplane = nullptr;//最近的敌机

    //遍历敌机池，找到最近的敌机
    double nearest_distance = 1000000;
    for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
        if (enemyplane->status != 2)continue;
        double px = enemyplane->pos().x() + enemyplane->pixmap().width() / 2, py = enemyplane->pos().y() + enemyplane->pixmap().width() / 2;
        double dx = x - px, dy = y - py;
        double distance = sqrt(dx * dx + dy * dy);
        if (distance < nearest_distance){
            nearest_distance = distance;
            nearest_enemyplane = enemyplane;
        }
    }

    if (nearest_enemyplane){//找到敌机
        // 计算敌机中心点
        double targetX = nearest_enemyplane->pos().x() + nearest_enemyplane->pixmap().width() / 2;
        double targetY = nearest_enemyplane->pos().y() + nearest_enemyplane->pixmap().height() / 2;

        double dx = x - targetX , dy = y - targetY;
        x -= (dx / nearest_distance) * speed;
        y -= (dy / nearest_distance) * speed;

        // 计算角度（弧度制）
        double radian = atan2(dy, dx);
        // 转换为角度制（Qt的旋转以度为单位，0度向右，逆时针为正）
        double angle = qRadiansToDegrees(radian) - 90; // 减90度使图片朝上为初始方向
        // 设置旋转角度
        setRotation(angle);
    }
    else{//未找到敌机
        y -= speed;
    }

    // 更新坐标
    setPos(x, y);
}

void HeroBullet::move4()
{
    // 基础向前移动（假设向上飞行，y轴递减）
    setY(y() - speed);  // speed是子弹的基础速度，需在类中定义或通过set_value设置

    // 曲线偏移计算：使用正弦函数实现横向摆动
    static double angle = 0;  // 角度变量，用于计算正弦值
    double offsetX = 30.0 * sin(angle);  // amplitude = 30.0是摆动幅度

    // 更新x坐标（加入横向偏移）
    setX(x() + offsetX);

    // 每次调用增加角度，控制摆动频率
    angle += 0.2;  // frequency = 0.2是摆动频率，值越大摆动越快

    // 防止角度过大导致精度问题，重置角度
    if (angle >= 2 * M_PI) {
        angle = 0;
    }
}

void HeroBullet::destroy()
{
    status = 0;
    setVisible(false);//设置图片不可见
}

void HeroBullet::collide_with_enemyplane(EnemyPlane* enemyplane)
{
    switch(bullet_kind){
    case 1:
        destroy();
        break;
    case 2:
        moveBy(0, -enemyplane->pixmap().height() + 5);
        break;
    case 3:
        destroy();
        break;
    case 4:
        destroy();
        break;
    }
}
