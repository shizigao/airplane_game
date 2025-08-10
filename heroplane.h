#ifndef HEROPLANE_H
#define HEROPLANE_H
#include "plane.h"
#include "heroweapon.h"
#include "herobullet.h"
#include "herobulletpool.h"
#include "enemybullet.h"
#include "enemyplane.h"
class HeroPlane:public Plane
{
public:
    HeroPlane();
    ~HeroPlane();
    //根据不同的英雄机种类初始化英雄机
    void init(int plane_kind);
    void init_1();
    void init_2();

    //发射第一个武器的子弹
    void weapon1_shoot(HeroBulletPool* herobullet_pool, QGraphicsScene* level_scene);
    //发射第二个武器的子弹
    void weapon2_shoot(HeroBulletPool* herobullet_pool, QGraphicsScene* level_scene);
    //发射第三个武器的子弹
    void weapon3_shoot(HeroBulletPool* herobullet_pool, QGraphicsScene* level_scene);

    //与敌机子弹发生碰撞
    void collide_with_enemybullet(EnemyBullet* enemybullet);
    //与敌机发生碰撞
    void collide_with_enemyplane(EnemyPlane* enemyplane);
    //升级函数
    void upgrade(QWidget* widget);
    //获取经验值比率
    int get_experience_rate();
public:
    //英雄机的种类
    int plane_kind = 1;
    //英雄机的三个武器槽
    HeroWeapon *weapon1 = nullptr, *weapon2 = nullptr, *weapon3 = nullptr;
    //护盾对象
    QGraphicsPixmapItem* shield = nullptr;
    //护盾的计时器
    QTimer* shield_timer = nullptr;
    //升级的图片
    QGraphicsPixmapItem* upgrade_picture;
    //当前经验值
    int experience = 0;
    //下一次升级所需经验值
    int next_level_experience = UPGRADE_EXPERIENCE;
    //当前等级
    int level = 1;


};

#endif // HEROPLANE_H
