#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include "plane.h"

class EnemyPlane: public Plane
{
public:
    EnemyPlane();
    EnemyPlane(int x, int y, QPixmap pixmap);


};

#endif // ENEMYPLANE_H
