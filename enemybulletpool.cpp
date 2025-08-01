#include "enemybulletpool.h"



EnemyBulletPool::EnemyBulletPool(QGraphicsScene *level_scene)
{
    this->level_scene = level_scene;
    enemybullet_pool_list = new QList<EnemyBullet*>();
    enemybullet_pool_queue = new QQueue<EnemyBullet*>();
}

EnemyBulletPool::EnemyBulletPool(QGraphicsScene *level_scene, int init_size)
{
    this->level_scene = level_scene;
    enemybullet_pool_list = new QList<EnemyBullet*>();
    enemybullet_pool_queue = new QQueue<EnemyBullet*>();
/*
    for (int i = 0; i < init_size; i++){
        EnemyBullet* new_enemybullet = new EnemyBullet();
        enemybullet_pool_list->append(new_enemybullet);
        enemybullet_pool_queue->append(new_enemybullet);
        new_enemybullet->status = 1;
        new_enemybullet->setVisible(false);
        level_scene->addItem(new_enemybullet);//把新建的敌机子弹加入场景
    }*/
}

EnemyBullet *EnemyBulletPool::get_new_enemybullet()
{
    EnemyBullet* res = nullptr;
    if (enemybullet_pool_queue->isEmpty()){
        EnemyBullet* new_enemybullet = new EnemyBullet();
        enemybullet_pool_list->append(new_enemybullet);
        level_scene->addItem(new_enemybullet);//把新建的敌机子弹加入场景
        res = new_enemybullet;
    }
    else{
        res = enemybullet_pool_queue->dequeue();
    }
    res->setVisible(true);
    res->status = 2;
    return res;
}

void EnemyBulletPool::return_enemybullet(EnemyBullet *enemybullet)
{
    enemybullet->status = 1;
    enemybullet_pool_queue->append(enemybullet);
}
