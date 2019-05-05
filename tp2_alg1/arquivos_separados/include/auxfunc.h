#ifndef AUX_H_INCLUDED
#define AUX_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define earthRadiusKm 6371.0

double deg2rad(double deg);

int distanceEarthKm(double lat1d, double lon1d, double lat2d, double lon2d);

int selectElement(int* vec, int size, int k);

int read(FILE* fp, char* buffer);

int medianOfFive(int* vec);

void selectionSort(int* vec, int size);

#endif // AUX_H_INCLUDED
