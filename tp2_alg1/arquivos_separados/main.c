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

    graph new_graph = graph_create(num_cities);

    for (i = 1; i < num_cities; i++)
    {
        for (j = 0; j < i; j++)
        {
            temp_i = city_getdist(&(city_vec[i]), &(city_vec[j]));
            graph_addEdge(&new_graph, i, j, temp_i);
        }
    }

    printf("%d", graph_findBottleneckEdge(&new_graph));

/*
    graph_print(&new_graph);

    graph new_graph2 = graph_duplicateGraph(&new_graph);
    graph_removeGreaterThen(&new_graph, 5000);

    graph_print(&new_graph);

    int *k = graph_checkConnectivity(&new_graph);
    graph_print(&new_graph2);
    graph new_graph3 = graph_collapse(&new_graph2, k);

    graph_print(&new_graph3);

    printf("test");

*/
    return 0;
}
