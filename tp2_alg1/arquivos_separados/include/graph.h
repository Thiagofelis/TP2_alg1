#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "auxfunc.h"

typedef struct edge
{
    int vertex;
    int cost;
    struct edge* next;
} edge;

typedef struct graph
{
    int num_v;
    edge** adj_list;
} graph;

typedef struct edge_array
{
    int array_size;
    int *array_pointer;
} edge_array;

graph graph_create(int _num_v);

void graph_addEdge(graph *gp, int v, int u, int _cost);

void graph_addSingleEdge(graph *gp, int v, int u, int _cost);

void graph_print(graph *gp);

graph graph_duplicateGraph(graph *gp);

void graph_removeGreaterThenOrEqual(graph *gp, int w);

void graph_removeGreaterThen(graph *gp, int w);

edge_array* graph_getWeigths(graph *gp);

void graph_ccRecursive(graph *gp, int* connected, int component_num, int starting_node, int* discovered);

int* graph_getConnectedComponents(graph *gp);

graph graph_collapse(graph *gp, int* connected);

void graph_deleteGraph(graph* gp);

int graph_findBERecursive(graph* gp);

int graph_findBERecursive(graph* gp);

int graph_findBottleneckEdge(graph* gp);

#endif // GRAPH_H_INCLUDED
