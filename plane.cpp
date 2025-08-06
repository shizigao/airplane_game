#include "plane.h"

Plane::Plane()
{

}

double Plane::get_health_rate()
{
    return health / max_health * 100;
}
