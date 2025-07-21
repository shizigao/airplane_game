#ifndef HEROBULLET_H
#define HEROBULLET_H
#include "bullet.h"

class HeroBullet: public Bullet
{
public:
    HeroBullet();
    HeroBullet(int x, int y, QPixmap pixmap);

};

#endif // HEROBULLET_H
