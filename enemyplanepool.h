#ifndef ENEMYPLANEPOOL_H
#define ENEMYPLANEPOOL_H
#include "enemyplane.h"
#include "config.h"
#include "QQueue"
#include "QList"

class EnemyPlanePool
{
public:
    EnemyPlanePool(QGraphicsScene* level_scene);
    EnemyPlanePool(QGraphicsScene* level_scene, int init_size);

    EnemyPlane* get_new_enemyplane();
    void return_enemyplane(EnemyPlane* enemyplane);

public:
    QQueue<EnemyPlane*>* enemyplane_pool_queue = nullptr;
    QList<EnemyPlane*>* enemyplane_pool_list = nullptr;
    //场景的指针
    QGraphicsScene* level_scene = nullptr;
};

#endif // ENEMYPLANEPOOL_H
