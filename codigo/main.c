#include <stdio.h>
#include <stdlib.h>
#include "include/auxfunc.h"
#include "include/graph.h"
#include "include/cities.h"


int main(int argc, char** argv)
{
    FILE* fp = fopen(argv[1], "r");
    char buffer[20];

    read(fp, buffer);
    int num_cities = atoi(buffer);

    city city_vec[num_cities];

    int i, j;
    float temp_f;
    for(i = 0; i < num_cities; i++)
    {
        read(fp, buffer);
        temp_f = atof(buffer);
        read(fp, buffer);
        city_vec[i] = city_init(temp_f, atof(buffer));
    }
    int temp_i;
	fclose(fp);
	graph *new_graph = (graph*) malloc(sizeof(graph));
    *new_graph = graph_create(num_cities);

    for (i = 1; i < num_cities; i++)
    {
        for (j = 0; j < i; j++)
        {
            temp_i = city_getdist(&(city_vec[i]), &(city_vec[j]));
            graph_addEdge(new_graph, i, j, temp_i);
        }
    }

    printf("%d", graph_findBottleneckEdge(new_graph));

	// we don't need to delete the graph because
	// graph_findBottleneckEdge already does that
	
    return 0;
}
