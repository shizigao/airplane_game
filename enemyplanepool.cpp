#include "enemyplanepool.h"



EnemyPlanePool::EnemyPlanePool(QGraphicsScene *level_scene)
{
    this->level_scene = level_scene;

}

EnemyPlanePool::EnemyPlanePool(QGraphicsScene *level_scene, int init_size)
{
    this->level_scene = level_scene;

    enemyplane_pool_list = new QList<EnemyPlane*>();
    enemyplane_pool_queue = new QQueue<EnemyPlane*>();
    for (int i = 0; i < init_size; i++){
        EnemyPlane* new_enemyplane = new EnemyPlane();
        enemyplane_pool_list->append(new_enemyplane);
        enemyplane_pool_queue->append(new_enemyplane);
        new_enemyplane->status = 1;
        new_enemyplane->setVisible(false);
        level_scene->addItem(new_enemyplane);//把新建的敌机加入场景
    }

}

EnemyPlane *EnemyPlanePool::get_new_enemyplane()
{
    EnemyPlane* res = nullptr;
    if (enemyplane_pool_queue->isEmpty()){
        EnemyPlane* new_enemyplane = new EnemyPlane();
        enemyplane_pool_list->append(new_enemyplane);
        level_scene->addItem(new_enemyplane);//把新建的敌机加入场景
        res = new_enemyplane;
    }
    else{
        res = enemyplane_pool_queue->dequeue();
    }
    res->setVisible(true);
    res->status = 2;
    return res;
}

void EnemyPlanePool::return_enemyplane(EnemyPlane *enemyplane)
{
    enemyplane->status = 1;
    enemyplane_pool_queue->append(enemyplane);
}
