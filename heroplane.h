#ifndef HEROPLANE_H
#define HEROPLANE_H

#include "plane.h"

class HeroPlane: public Plane
{
public:
    HeroPlane();
    HeroPlane(int x, int y, QPixmap pixmap);


};

#endif // HEROPLANE_H
