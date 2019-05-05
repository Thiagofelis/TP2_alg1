#include "../include/cities.h"

city city_init (float _latit, float _longit)
{
    city new_city;
    new_city.latit = _latit;
    new_city.longit = _longit;
    return new_city;
}

int city_getdist(city *c1, city *c2)
{
    return distanceEarthKm(c1->latit, c1->longit, c2->latit, c2->longit);
}
