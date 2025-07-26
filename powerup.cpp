#include "powerup.h"
#include "heroplane.h"
#include <random>
#include <QPainter>

PowerUp::PowerUp()
{
    effect_timer = new QTimer();
    effect_timer->setSingleShot(true); // 效果计时器只执行一次
}

PowerUp::~PowerUp()
{
    if (effect_timer) {
        effect_timer->stop();
        delete effect_timer;
    }
}

void PowerUp::init(double x, double y, int type)
{
    powerup_type = type;
    setPos(x, y);
    setVisible(true);
    status = 2;
    speed = POWERUP_SPEED;

    switch (type) {
    case POWERUP_TYPE_FIREPOWER:
        init_firepower();
        break;
    case POWERUP_TYPE_HEALTH:
        init_health();
        break;
    case POWERUP_TYPE_BOMB:
        init_bomb();
        break;
    case POWERUP_TYPE_SHIELD:
        init_shield();
        break;
    case POWERUP_TYPE_EXP:
        init_exp();
        break;
    default:
        init_firepower(); // 默认为火力增强
        break;
    }
}

void PowerUp::init_firepower()
{
    // 由于没有图片资源，我们用一个红色方块代替
    QPixmap pixmap(30, 30);
    pixmap.fill(QColor(255, 100, 100, 200)); // 半透明红色
    setPixmap(pixmap);
    effect_duration = POWERUP_FIREPOWER_DURATION;
}

void PowerUp::init_health()
{
    // 绿色十字代表生命恢复
    QPixmap pixmap(30, 30);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(QColor(100, 255, 100, 200)); // 半透明绿色
    painter.setPen(Qt::NoPen);
    // 画十字
    painter.drawRect(10, 5, 10, 20);  // 竖线
    painter.drawRect(5, 10, 20, 10);  // 横线
    setPixmap(pixmap);
    health_restore = POWERUP_HEALTH_RESTORE;
}

void PowerUp::init_bomb()
{
    // 橙色圆形代表炸弹
    QPixmap pixmap(30, 30);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(QColor(255, 165, 0, 200)); // 半透明橙色
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(3, 3, 24, 24);
    setPixmap(pixmap);
}

void PowerUp::init_shield()
{
    // 蓝色盾牌形状代表护盾
    QPixmap pixmap(30, 30);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(QColor(100, 100, 255, 200)); // 半透明蓝色
    painter.setPen(Qt::NoPen);
    // 简单的盾牌形状（圆角矩形）
    painter.drawRoundedRect(5, 3, 20, 24, 10, 10);
    setPixmap(pixmap);
    effect_duration = POWERUP_SHIELD_DURATION;
}

void PowerUp::init_exp()
{
    // 金色星形代表经验加成
    QPixmap pixmap(30, 30);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(QColor(255, 215, 0, 200)); // 半透明金色
    painter.setPen(Qt::NoPen);
    // 简单的星形（用多个三角形组成）
    QPolygon star;
    star << QPoint(15, 3) << QPoint(18, 12) << QPoint(27, 12)
         << QPoint(20, 18) << QPoint(23, 27) << QPoint(15, 21)
         << QPoint(7, 27) << QPoint(10, 18) << QPoint(3, 12)
         << QPoint(12, 12);
    painter.drawPolygon(star);
    setPixmap(pixmap);
    exp_bonus = POWERUP_EXP_BONUS;
}

void PowerUp::destroy()
{
    status = 0;
    setVisible(false);
    if (effect_timer) {
        effect_timer->stop();
    }
}

void PowerUp::move()
{
    double x = pos().x(), y = pos().y();
    y += speed;
    setPos(x, y);
}

void PowerUp::is_live()
{
    // 检测道具是否出界
    double x = pos().x(), y = pos().y();
    if ((y >= VIEW_HEIGHT || x <= -50 || x >= VIEW_WIDTH + 50) && status == 2) {
        destroy();
    }
}

void PowerUp::apply_effect(HeroPlane* heroplane)
{
    if (!heroplane || heroplane->status != 2) return;

    switch (powerup_type) {
    case POWERUP_TYPE_FIREPOWER:
        {
            // 火力增强：提升所有武器伤害50%
            if (heroplane->weapon1) {
                heroplane->weapon1->damage *= 1.5;
            }
            if (heroplane->weapon2) {
                heroplane->weapon2->damage *= 1.5;
            }
            if (heroplane->weapon3) {
                heroplane->weapon3->damage *= 1.5;
            }

            // 设置定时器，效果持续一段时间后恢复
            effect_timer->start(effect_duration);
            // 注意：这里需要在widget中连接信号槽来处理效果结束
        }
        break;

    case POWERUP_TYPE_HEALTH:
        {
            // 生命恢复：恢复指定生命值，不超过最大生命值
            heroplane->health += health_restore;
            if (heroplane->health > heroplane->max_health) {
                heroplane->health = heroplane->max_health;
            }
        }
        break;

    case POWERUP_TYPE_BOMB:
        {
        if (heroplane->bomb_count < heroplane->max_bomb_count) {
                        heroplane->bomb_count++;
                    }
        }
        break;

    case POWERUP_TYPE_SHIELD:
        {
            // 护盾强化：启动更强的护盾效果
            heroplane->shield->setVisible(true);
            heroplane->shield->setOpacity(0.8); // 更强的护盾透明度更高
            heroplane->invincible_timer->start(effect_duration);
        }
        break;

    case POWERUP_TYPE_EXP:
        {
            // 经验加成：直接增加经验值
            heroplane->experience += exp_bonus;
        }
        break;
    }

    // 道具被拾取后销毁
    destroy();
}
