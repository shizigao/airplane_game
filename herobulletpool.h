#ifndef HEROBULLETPOOL_H
#define HEROBULLETPOOL_H
#include "herobullet.h"
#include "config.h"
#include "QQueue"
#include "QList"
class HeroBulletPool
{
public:
    HeroBulletPool(QGraphicsScene* level_scene);
    HeroBulletPool(QGraphicsScene* level_scene, int init_size);

    HeroBullet* get_new_herobullet();
    void return_herobullet(HeroBullet* herobullet);

public:
    QQueue<HeroBullet*>* herobullet_pool_queue = nullptr;
    QList<HeroBullet*>* herobullet_pool_list = nullptr;
    //场景的指针
    QGraphicsScene* level_scene = nullptr;
};

#endif // HEROBULLETPOOL_H
