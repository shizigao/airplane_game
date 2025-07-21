#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include "bullet.h"

class EnemyBullet: public Bullet
{
public:
    EnemyBullet();
    EnemyBullet(int x, int y, QPixmap pixmap);
};

#endif // ENEMYBULLET_H
