#ifndef ENEMYBULLETPOOL_H
#define ENEMYBULLETPOOL_H

#include "config.h"
#include "QQueue"
#include "QList"
#include "enemybullet.h"

class EnemyBulletPool
{
public:
    EnemyBulletPool(QGraphicsScene* level_scene);
    EnemyBulletPool(QGraphicsScene* level_scene, int init_size);

    EnemyBullet* get_new_enemybullet();
    void return_enemybullet(EnemyBullet* enemybullet);

public:

    QList<EnemyBullet*>* enemybullet_pool_list = nullptr;
    QQueue<EnemyBullet*>* enemybullet_pool_queue = nullptr;
    //场景的指针
    QGraphicsScene* level_scene = nullptr;

};

#endif // ENEMYBULLETPOOL_H
