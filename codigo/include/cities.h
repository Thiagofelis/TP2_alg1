#ifndef CITIES_H_INCLUDED
#define CITIES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "auxfunc.h"

typedef struct city
{
    float latit, longit;
} city;

city city_init (float _latit, float _longit);

int city_getdist(city *c1, city *c2);

#endif // CITIES_H_INCLUDED
