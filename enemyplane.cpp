#include "enemyplane.h"
#include "herobullet.h"
#include "heroplane.h"

class Widget;
void EnemyPlane::init(double x, double y, int kind)
{
    this->setVisible(true);
    status = 2;
    setPos(x, y);
    this->plane_kind = kind;

    // 重置Boss相关属性
    boss_phase = 1;
    attack_pattern_timer = 0;
    movement_timer = 0;
    is_entering = true;
    special_attack_cooldown = 0;

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
        init_boss1();
        break;
    case 6:
        init_boss2();
        break;
    default:
        break;
    }
    health *= difficulty_degree;//实现难度逐渐提升
    damage *= difficulty_degree;
}

EnemyPlane::EnemyPlane(QTimer *weapon_timer)
{
    this->weapon_timer = weapon_timer;
}

EnemyPlane::~EnemyPlane()
{
    if (weapon)delete weapon;
    if (weapon_timer){
        delete weapon_timer;
    }
}

void EnemyPlane::init_1()
{
    setPixmap(QPixmap(ENEMYPLANE_PICTURE1));
    speed = ENEMYPLANE1_SPEED;
    health = ENEMYPLANE1_HEALTH;
    damage = ENEMYPLANE1_DAMAGE;
    score = ENEMYPLANE1_SCORE;
    //对应第一种武器
    weapon = new EnemyWeapon();
    weapon->init(1);
    //开启武器计时器
    weapon_timer->start(weapon->interval);
}

void EnemyPlane::init_2()
{
    setPixmap(QPixmap(ENEMYPLANE_PICTURE2));
    speed = ENEMYPLANE2_SPEED;
    health = ENEMYPLANE2_HEALTH;
    damage = ENEMYPLANE2_DAMAGE;
    score = ENEMYPLANE2_SCORE;

    // 第二种武器
    weapon = new EnemyWeapon();
    weapon->init(2);
    // 开启武器计时器
    weapon_timer->start(weapon->interval);
}

void EnemyPlane::init_3()
{
    setPixmap(QPixmap(ENEMYPLANE_PICTURE3));
    speed = ENEMYPLANE3_SPEED;
    health = ENEMYPLANE3_HEALTH;
    damage = ENEMYPLANE3_DAMAGE;
    score = ENEMYPLANE3_SCORE;

    // 第三种武器
    weapon = new EnemyWeapon();
    weapon->init(3);
    // 开启武器计时器
    weapon_timer->start(weapon->interval);
}

void EnemyPlane::init_4()
{
    setPixmap(QPixmap(ENEMYPLANE_PICTURE4));
    speed = ENEMYPLANE4_SPEED;
    health = ENEMYPLANE4_HEALTH;
    damage = ENEMYPLANE4_DAMAGE;
    score = ENEMYPLANE4_SCORE;

    // 第四种武器
    weapon = new EnemyWeapon();
    weapon->init(4);
    // 开启武器计时器
    weapon_timer->start(weapon->interval);
}

void EnemyPlane::init_boss1()
{
    setPixmap(QPixmap(BOSS_PICTURE1));
    speed = BOSS1_SPEED;
    health = BOSS1_HEALTH;
    max_health = BOSS1_HEALTH * difficulty_degree;
    damage = BOSS1_DAMAGE;
    score = BOSS1_SCORE;

    // Boss专用武器
    weapon = new EnemyWeapon();
    weapon->init(5); // Boss武器种类5
    // 设置更短的攻击间隔
    weapon_timer->start(weapon->interval / 2);

    // 设置Boss初始位置（从屏幕上方进入）
    target_x = VIEW_WIDTH / 2 - pixmap().width() / 2;
    target_y = 100; // 停留在屏幕上方
}

void EnemyPlane::init_boss2()
{
    setPixmap(QPixmap(BOSS_PICTURE2));
    speed = BOSS2_SPEED;
    health = BOSS2_HEALTH;
    max_health = BOSS2_HEALTH;
    damage = BOSS2_DAMAGE;
    score = BOSS2_SCORE;

    // Boss专用武器
    weapon = new EnemyWeapon();
    weapon->init(6); // Boss武器种类6
    weapon_timer->start(weapon->interval / 2);

    // 设置Boss初始位置
    target_x = VIEW_WIDTH / 2 - pixmap().width() / 2;
    target_y = 80;
}

void EnemyPlane::destroy()
{
    status = 0;
    setVisible(false);
    weapon_timer->stop();
}

void EnemyPlane::move(HeroPlane* heroplane1, HeroPlane*heroplane2)
{
    switch(plane_kind){
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
        move_boss1();
        break;
    case 6:
        move_boss2();
        break;
    }
}

void EnemyPlane::move_1()
{
    double y = pos().y(), x = pos().x();
    y += speed;
    setPos(x, y);
}

void EnemyPlane::move_2()
{
    // 左右摇摆向下移动
    static double angle = 0;
    double x = pos().x();
    double y = pos().y();

    // 向下移动
    y += speed;
    // 左右摇摆，使用正弦函数
    x += 3 * sin(angle);
    angle += 0.1;

    setPos(x, y);
}

void EnemyPlane::move_3()
{
    // 快速斜向移动，随机改变方向
    static int dir = 1; // 1向右，-1向左
    static int changeTimer = 0;

    double x = pos().x();
    double y = pos().y();

    y += speed;
    x += dir * 2;

    // 每隔一定时间改变方向
    changeTimer++;
    if (changeTimer >= 50) {
        changeTimer = 0;
        dir = (rand() % 2 == 0) ? 1 : -1;
    }

    // 边界检查
    if (x <= 0) x = 0;
    if (x >= 800) x = 800;

    setPos(x, y);
}

void EnemyPlane::move_4(HeroPlane* heroplane1, HeroPlane* heroplane2)
{
    // 跟踪最近英雄机移动
    int flag = 1;
    if( heroplane1 && heroplane2 ){
        double x1 = abs(heroplane1->pos().x() - this->pos().x());
        double x2 = abs(heroplane2->pos().x() - this->pos().x());
        double y1 = abs(heroplane1->pos().y() - this->pos().y());
        double y2 = abs(heroplane2->pos().y() - this->pos().y());
        if (x1 + y1 < x2 + y2){//飞机离英雄机1更近
            flag = 1;
        }
        else{//飞机离英雄机2更近
            flag = 2;
        }
    }
    if (heroplane1 && flag == 1) { // 假设heroplane1是玩家1飞机
        double heroX = heroplane1->pos().x();
        double x = pos().x();
        double y = pos().y();

        y += speed;

        // 缓慢向英雄机X坐标靠近
        if (x < heroX - 10) {
            x += speed * 0.5;
        } else if (x > heroX + 10) {
            x -= speed * 0.5;
        }

        setPos(x, y);
    } else {
        // 如果找不到英雄机，默认向下移动
        double y = pos().y();
        y += speed;
        setPos(pos().x(), y);
    }
    if (heroplane2 && flag == 2) { // 假设heroplane1是玩家1飞机
        double heroX = heroplane2->pos().x();
        double x = pos().x();
        double y = pos().y();
        y += speed;

        // 缓慢向英雄机X坐标靠近
        if (x < heroX - 10) {
            x += speed * 0.5;
        } else if (x > heroX + 10) {
            x -= speed * 0.5;
        }

        setPos(x, y);
    } else {
        // 如果找不到英雄机，默认向下移动
        double y = pos().y();
        y += speed;
        setPos(pos().x(), y);
    }
}

void EnemyPlane::move_boss1()
{
    movement_timer += GAME_PERIOD;

    if (is_entering) {
        // Boss进入阶段：从上方缓慢进入
        double current_x = pos().x();
        double current_y = pos().y();

        // 移动到目标位置
        if (abs(current_x - target_x) > 5) {
            current_x += (target_x - current_x) * 0.02;
        }
        if (abs(current_y - target_y) > 5) {
            current_y += (target_y - current_y) * 0.02;
        } else {
            is_entering = false; // 到达目标位置，结束进入阶段
        }

        setPos(current_x, current_y);
    } else {
        // Boss战斗阶段：根据当前阶段执行不同的移动模式
        switch(boss_phase) {
        case 1:
            // 第一阶段：左右缓慢移动
            if (movement_timer % 3000 < 1500) {
                target_x = 100;
            } else {
                target_x = VIEW_WIDTH - pixmap().width() - 100;
            }
            break;
        case 2:
            // 第二阶段：更快的左右移动 + 上下移动
            if (movement_timer % 2000 < 1000) {
                target_x = 50;
                target_y = 80;
            } else {
                target_x = VIEW_WIDTH - pixmap().width() - 50;
                target_y = 150;
            }
            break;
        case 3:
            // 第三阶段：复杂的8字移动
            double time = movement_timer * 0.001;
            target_x = VIEW_WIDTH/2 + 150 * sin(time);
            target_y = 100 + 30 * sin(2*time);
            break;
        }

        // 缓慢移动到目标位置
        double current_x = pos().x();
        double current_y = pos().y();
        current_x += (target_x - current_x) * 0.05;
        current_y += (target_y - current_y) * 0.05;
        setPos(current_x, current_y);
    }
}

void EnemyPlane::move_boss2()
{
    movement_timer += GAME_PERIOD;

    if (is_entering) {
        // Boss2进入阶段
        double current_x = pos().x();
        double current_y = pos().y();

        if (abs(current_x - target_x) > 5) {
            current_x += (target_x - current_x) * 0.025;
        }
        if (abs(current_y - target_y) > 5) {
            current_y += (target_y - current_y) * 0.025;
        } else {
            is_entering = false;
        }

        setPos(current_x, current_y);
    } else {
        // Boss2战斗阶段：更加激进的移动模式
        switch(boss_phase) {
        case 1:
            // 第一阶段：快速左右移动
            if (movement_timer % 2000 < 1000) {
                target_x = 80;
            } else {
                target_x = VIEW_WIDTH - pixmap().width() - 80;
            }
            break;
        case 2:
            // 第二阶段：螺旋移动
            {
                double time = movement_timer * 0.002;
                target_x = VIEW_WIDTH/2 + 100 * cos(time);
                target_y = 120 + 40 * sin(time);
            }
            break;
        case 3:
            // 第三阶段：随机瞬移
            if (movement_timer % 1500 == 0) {
                target_x = rand() % (VIEW_WIDTH - pixmap().width());
                target_y = 60 + rand() % 100;
            }
            break;
        }

        // 更快的移动速度
        double current_x = pos().x();
        double current_y = pos().y();
        current_x += (target_x - current_x) * 0.08;
        current_y += (target_y - current_y) * 0.08;
        setPos(current_x, current_y);
    }
}

bool EnemyPlane::is_boss()
{
    return plane_kind == 5 || plane_kind == 6;
}

void EnemyPlane::update_boss_phase()
{
    if (!is_boss()) return;

    double health_ratio = (double)health / max_health;
    qDebug() << "boss health rate" << health_ratio;

    if (health_ratio <= BOSS_PHASE_2_HEALTH_RATIO && boss_phase == 1) {
        boss_phase = 2;
        // 阶段切换时重置攻击模式计时器
        attack_pattern_timer = 0;
        // 缩短攻击间隔
        weapon_timer->stop();
        weapon_timer->start(weapon->interval / 3);
    } else if (health_ratio <= BOSS_PHASE_3_HEALTH_RATIO  && boss_phase == 2) {
        boss_phase = 3;
        attack_pattern_timer = 0;
        // 进一步缩短攻击间隔
        weapon_timer->stop();
        weapon_timer->start(weapon->interval / 4);
    }
}

void EnemyPlane::boss_attack_pattern_1()
{
    // 攻击模式1：直线攻击（基础攻击）
    // 这个函数会在武器计时器触发时被调用
    // 具体的子弹发射逻辑在widget.cpp的enemyplane_shoot函数中实现
}

void EnemyPlane::boss_attack_pattern_2()
{
    // 攻击模式2：散弹攻击
    // 发射多个方向的子弹
}

void EnemyPlane::boss_attack_pattern_3()
{
    // 攻击模式3：弹幕攻击
    // 发射大量密集的子弹
}

void EnemyPlane::boss_special_attack()
{
    // Boss特殊攻击
    if (special_attack_cooldown > 0) {
        special_attack_cooldown -= GAME_PERIOD;
        return;
    }

    // 每个阶段的特殊攻击间隔不同
    int cooldown_time = 5000 - (boss_phase - 1) * 1000; // 5秒、4秒、3秒
    special_attack_cooldown = cooldown_time;
}

void EnemyPlane::is_live()
{
    // 更新Boss阶段
    if (is_boss()) {
        update_boss_phase();
    }

    double x = pos().x(), y = pos().y();
    //超过边界则死亡（Boss除外）
    if (y >= 1200 && status == 2 && !is_boss()){
        destroy();
    }
    //生命值降为负数则死亡
    if (health <= 0 && status == 2){
        destroy();
    }
}

void EnemyPlane::collide_with_herobullet(HeroBullet *herobullet)
{
    health -= herobullet->damage;
}

void EnemyPlane::collide_with_heroplane(HeroPlane *heroplane)
{
    health -= heroplane->damage;
}

double EnemyPlane::difficulty_degree = 1.0;
