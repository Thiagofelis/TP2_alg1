#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	srand(atoi(argv[3]));

    int num_cities = atoi(argv[1]);
    FILE *fp = fopen(argv[2], "w");
    fprintf(fp, "%d\n", num_cities);

    int i;
    double latit, longit;

    for (i = 0; i < num_cities; i++)
    {
        latit = (180.0 * ( (float) rand() / (RAND_MAX+1.0) ) ) - 90.0;
        longit = (360.0 * ( (float) rand() / (RAND_MAX+1.0) ) ) - 180.0;
        fprintf(fp, "%f %f\n", latit, longit);
    }

    fclose(fp);
    return 0;
}
