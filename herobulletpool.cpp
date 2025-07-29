#include "herobulletpool.h"

HeroBulletPool::HeroBulletPool(QGraphicsScene* level_scene)
{
    this->level_scene = level_scene;

}

HeroBulletPool::HeroBulletPool(QGraphicsScene* level_scene, int init_size)
{
    this->level_scene = level_scene;

    herobullet_pool_list = new QList<HeroBullet*>();
    herobullet_pool_queue = new QQueue<HeroBullet*>();
    for (int i = 0; i < init_size; i++){
        HeroBullet* new_herobullet = new HeroBullet();
        herobullet_pool_list->append(new_herobullet);
        herobullet_pool_queue->append(new_herobullet);
        new_herobullet->status = 1;
        new_herobullet->setVisible(false);
        level_scene->addItem(new_herobullet);//把新建的子弹加入场景
    }
}

HeroBullet *HeroBulletPool::get_new_herobullet()
{
    HeroBullet* res = nullptr;
    if (herobullet_pool_queue->isEmpty()){
        HeroBullet* new_herobullet = new HeroBullet();
        herobullet_pool_list->append(new_herobullet);
        level_scene->addItem(new_herobullet);//把新建的子弹加入场景
        res = new_herobullet;
    }
    else{
        res = herobullet_pool_queue->dequeue();
    }
    res->setVisible(true);
    res->status = 2;
    return res;
}

void HeroBulletPool::return_herobullet(HeroBullet *herobullet)
{
    herobullet->status = 1;
    herobullet_pool_queue->append(herobullet);
}
