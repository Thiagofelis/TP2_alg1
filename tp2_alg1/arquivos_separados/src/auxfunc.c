#include "../include/auxfunc.h"
#include <math.h>

#define earthRadiusKm 6371.0

double deg2rad(double deg)
{
    return (deg * M_PI / 180);
}

int distanceEarthKm(double lat1d, double lon1d, double lat2d, double lon2d)
{
    double lat1r, lat2r, lon1r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r-lat1r)/2);
    v = sin((lon2r-lon1r)/2);
    return (int) 2.0 * earthRadiusKm * asin(sqrt(u*u+cos(lat1r)*cos(lat2r)*v*v));
}

int read(FILE* fp, char* buffer)
{
    int i = 0;
    char temp;
    do{
        temp = fgetc(fp);
    } while ((temp == ' ') || (temp == '\n') || (temp == '\r'));

    while ((temp != ' ') && (temp != '\n') && (temp != '\r') && (temp != EOF))
    {
        buffer[i] = temp;
        i++;
        temp = fgetc(fp);
    }
    buffer[i] = '\0';

    if (buffer[0] == '\0')
    {
        printf("problema na formatacao\n");
        return EOF;
    }
    return 0;
}

int selectElement(int* vec, int size, int k)
{

    if (size < 100)
    {
        selectionSort(vec, size);
        return vec[k];
    }

    int *vec_of_med = (int*) malloc((size / 5) * sizeof(int));
    int i;
    for (i = 0; i < size / 5; i++)
    {
        vec_of_med[i] = medianOfFive(vec + 5 * i);
    }

    int median_of_medians = selectElement(vec_of_med, size / 5, size / 10);

    free(vec_of_med);

    int *gt_median = (int*) malloc(size * sizeof(int));
    int *lt_median = (int*) malloc(size * sizeof(int));
    int *eq_median = (int*) malloc(size * sizeof(int));
    int gtm_vec_size = 0, ltm_vec_size = 0, eqm_vec_size = 0;

    for (i = 0; i < size; i++)
    {
        if (vec[i] == median_of_medians)
        {
            eq_median[eqm_vec_size++] = vec[i];
        }
        else
        {
            if (vec[i] > median_of_medians)
            {
                gt_median[gtm_vec_size++] = vec[i];
            }
            else
            {
                lt_median[ltm_vec_size++] = vec[i];
            }
        }
    }


    if (k < ltm_vec_size)
    {
        free(eq_median);
        free(gt_median);
        return selectElement(lt_median, ltm_vec_size, k);
    }
    else
    {
        if (k < ltm_vec_size + eqm_vec_size)
        {
            free(eq_median);
            free(gt_median);
            free(lt_median);
            return median_of_medians;
        }
        else
        {
            free(eq_median);
            free(lt_median);
            return selectElement(gt_median, gtm_vec_size, k - ltm_vec_size - eqm_vec_size);
        }
    }
}

int medianOfFive(int* vec)
{
    int temp_vec[5];
    int i;
    for (i = 0; i < 5; i++)
    {
        temp_vec[i] = vec[i];
    }

    selectionSort(temp_vec, 5);
    return temp_vec[2];
}

void selectionSort(int* vec, int size)
{
    int i, j, temp;
    for (i = 0; i < size; i++)
    {
        for (j = i; j < size; j++)
        {
            if (vec[i] > vec[j])
            {
                temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

