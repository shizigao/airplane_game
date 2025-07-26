#include "enemybullet.h"
#include "heroplane.h"
EnemyBullet::EnemyBullet()
{

}


void EnemyBullet::init(double x, double y, int kind)
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
    case 5:
        init_boss_bullet_1();
        break;
    case 6:
        init_boss_bullet_2();
        break;
    case 7:
        init_boss_bullet_3();
        break;
    default:
        break;
    }

}

void EnemyBullet::init_1()
{
    setPixmap(QPixmap(ENEMYBULLET_PICTURE1));
}

void EnemyBullet::init_2()
{
     setPixmap(QPixmap(ENEMYBULLET_PICTURE2));
}

void EnemyBullet::init_3()
{
    setPixmap(QPixmap(ENEMYBULLET_PICTURE3));
}

void EnemyBullet::init_4()
{
    setPixmap(QPixmap(ENEMYBULLET_PICTURE4));
}

void EnemyBullet::init_boss_bullet_1()
{
    setPixmap(QPixmap(BOSS_BULLET_PICTURE1));
}

void EnemyBullet::init_boss_bullet_2()
{
    setPixmap(QPixmap(BOSS_BULLET_PICTURE2));
}

void EnemyBullet::init_boss_bullet_3()
{
    setPixmap(QPixmap(BOSS_BULLET_PICTURE3));
}

void EnemyBullet::destroy()
{
    status = 0;
    setVisible(false);
}

void EnemyBullet::move(HeroPlane* heroplane1, HeroPlane* heroplane2)
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
        move_4(heroplane1, heroplane2);
        break;

    case 5:
        move_boss_bullet_1();
        break;

    case 6:
        move_boss_bullet_2();
        break;

    case 7:
        move_boss_bullet_3(heroplane1, heroplane2);
        break;
    }
}

void EnemyBullet::move_1()
{
    double x = pos().x(), y = pos().y();
    y += speed;
    setPos(x, y);
}

void EnemyBullet::move_2()
{
    // 散弹效果，稍微向左下方移动
    double x = pos().x();
    double y = pos().y();
    y += speed;
    x -= 1; // 向左偏移
    setPos(x, y);
}

void EnemyBullet::move_3()
{
    // 散弹效果，稍微向右下方移动
    double x = pos().x();
    double y = pos().y();
    y += speed;
    x += 1; // 向右偏移
    setPos(x, y);
}

void EnemyBullet::move_4(HeroPlane* heroplane1, HeroPlane* heroplane2)
{
    static int count = 0;//追踪弹一段时间后会销毁
    if (count == 4000){
        count = 0;
        destroy();
    }
    int flag = 1;
    // 跟踪英雄机的子弹
    if (heroplane1 && heroplane2){
        double x1 = abs(heroplane1->pos().x() - this->pos().x());
        double x2 = abs(heroplane2->pos().x() - this->pos().x());
        double y1 = abs(heroplane1->pos().y() - this->pos().y());
        double y2 = abs(heroplane2->pos().y() - this->pos().y());
        if (x1 + y1 < x2 + y2){//离英雄机1更近
            flag = 1;
        }
        else { //离英雄机2更近
            flag = 2;
        }
    }
    if (heroplane1 && flag == 1) {
        double heroX = heroplane1->pos().x();
        double heroY = heroplane1->pos().y();
        double x = pos().x();
        double y = pos().y();

        // 计算朝向英雄机的方向
        double dx = heroX - x;
        double dy = heroY - y;
        double distance = sqrt(dx*dx + dy*dy);
        if (distance > 0) {
            x += (dx / distance) * speed;
            y += (dy / distance) * speed;
        }
        setPos(x, y);
    }

    if (heroplane2 && flag == 2) {
        double heroX = heroplane2->pos().x();
        double heroY = heroplane2->pos().y();
        double x = pos().x();
        double y = pos().y();

        // 计算朝向英雄机的方向
        double dx = heroX - x;
        double dy = heroY - y;
        double distance = sqrt(dx*dx + dy*dy);

        if (distance > 0) {
            x += (dx / distance) * speed;
            y += (dy / distance) * speed;
        }

        setPos(x, y);
    }
    count += GAME_PERIOD;
}

void EnemyBullet::move_boss_bullet_1()
{
    // Boss子弹1：直线快速移动
    double x = pos().x(), y = pos().y();
    y += speed;
    setPos(x, y);
}

void EnemyBullet::move_boss_bullet_2()
{
    // Boss子弹2：波浪形移动
    static double wave_time = 0;
    wave_time += 0.2;

    double x = pos().x();
    double y = pos().y();

    y += speed;
    x += 3 * sin(wave_time); // 波浪形左右摆动

    setPos(x, y);
}

void EnemyBullet::move_boss_bullet_3(HeroPlane* heroplane1, HeroPlane* heroplane2)
{
    // Boss子弹3：激光子弹，快速直线移动
    double x = pos().x(), y = pos().y();
    y += speed * 1.5; // 比普通子弹快1.5倍
    setPos(x, y);
}

void EnemyBullet::is_live()
{
    //检测子弹是否出界
    double x = pos().x(), y = pos().y();
    if ((y >= 1200 || x <= -100 || x >= 900) && status == 2){
        destroy();
    }
}

void EnemyBullet::set_value(EnemyWeapon *enemyweapon)
{
    damage = enemyweapon->damage;
    speed = enemyweapon->speed;
}

void EnemyBullet::collide_with_heroplane(HeroPlane *heroplane)
{
    switch(bullet_kind){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            destroy();
            break;
        }
}
