#include "../include/graph.h"

graph graph_create(int _num_v)
{	
	// on the chosen implementation, we allocate an array of edge*.
	// at position i, we put the head of the list of edges incident to node i
	
    graph new_graph;
    new_graph.num_v = _num_v;
    new_graph.adj_list = (edge**) malloc(_num_v * sizeof(edge*));

    edge* head;
    int i;
    for (i = 0; i < _num_v; i++)
    {
        head = (edge*) malloc(sizeof(edge));
        new_graph.adj_list[i] = head;
        head->cost = -1;
        head->vertex = -1;
        head->next = 0;
    }
    return new_graph;
}

void graph_addEdge(graph *gp, int v, int u, int _cost)
{
    graph_addSingleEdge(gp, v, u, _cost);
    graph_addSingleEdge(gp, u, v, _cost);
}

void graph_addSingleEdge(graph *gp, int v, int u, int _cost)
{
    edge* head = (gp->adj_list)[v];

    edge* ep = (edge*) malloc(sizeof(edge));
    ep->vertex = u;
    ep->cost = _cost;
    ep->next = head->next;
    head->next = ep;
}

void graph_print(graph *gp)
{
    int i;
    for (i = 0; i < gp->num_v; i++)
    {
        edge* temp = ((gp->adj_list)[i])->next;
        printf("edges incident to node %d: ", i);
        while (temp != 0)
        {
            printf("(%d to %d, %d), ", i, temp->vertex, temp->cost);
            temp = temp->next;
        }
        printf("\n");
    }
}

edge_array* graph_getWeights(graph *gp)
{
    int vec_size = ((float)(gp->num_v) * (float)(gp->num_v - 1)) / 2;

    int *vec = (int*) malloc(vec_size * sizeof(int));

    int *check_matrix = (int*) malloc(gp->num_v * gp->num_v * sizeof(int));
    int i, j;
    for (i = 0; i < gp->num_v; i++)
    {
        for (j = 0; j < gp->num_v; j++)
        {
            check_matrix[i + j * gp->num_v] = 0;
        }
    }
    int count = 0;

    for (i = 0; i < gp->num_v; i++)
    {
        edge* temp = ((gp->adj_list)[i])->next;
        while (temp != 0)
        {
            if (check_matrix[i + temp->vertex * gp->num_v] == 0)
            {
                vec[count] = temp->cost;
                count++;
                check_matrix[i + temp->vertex * gp->num_v] = 1;
                check_matrix[temp->vertex + i * gp->num_v] = 1;
            }
            temp = temp->next;
        }
    }

    free(check_matrix);

    edge_array *edge_vec = (edge_array*) malloc(sizeof(edge_array));
    edge_vec->array_size = count;
    edge_vec->array_pointer = vec;

    return edge_vec;
}

void graph_removeGreaterThenOrEqual(graph *gp, int w)
{
    int i;
    edge* temp;
    edge* temp2;

    for (i = 0; i < gp->num_v; i++)
    {
        temp = (gp->adj_list)[i];

        while (temp->next != 0)
        {
            if((temp->next)->cost >= w)
            {
                temp2 = (temp->next)->next;
                free(temp->next);
                temp->next = temp2;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
}

void graph_removeGreaterThen(graph *gp, int w)
{
    int i;
    edge* temp;
    edge* temp2;

    for (i = 0; i < gp->num_v; i++)
    {
        temp = (gp->adj_list)[i];

        while (temp->next != 0)
        {
            if((temp->next)->cost > w)
            {
                temp2 = (temp->next)->next;
                free(temp->next);
                temp->next = temp2;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
}

graph graph_duplicateGraph(graph *gp)
{
    graph new_graph = graph_create(gp->num_v);

    int i;
    for (i = 0; i < gp->num_v; i++)
    {
        edge* temp = ((gp->adj_list)[i])->next;
        while (temp != 0)
        {
            graph_addSingleEdge(&new_graph, i, temp->vertex, temp->cost);
            temp = temp->next;
        }
    }
    return new_graph;
}

int* graph_getConnectedComponents(graph *gp)
{ // returns a vector that indicates all the CCs in the graph.
  // if vec[i] = j, than the node i is reachable by node j.
  // node j is called the parent node, and this CC is named j.

    int *connected = (int*) malloc(gp->num_v * sizeof(int));

    // marks the nodes that were already discovered
    int *discovered = (int*) malloc(gp->num_v * sizeof(int));

    int i;
    for(i = 0; i < gp->num_v; i++)
    {   // each node starts as the parent node of its connected component
        connected[i] = i;
        discovered[i] = 0;
    }

    // starts the search at node 0
    discovered[0] = 1;
    graph_ccRecursive(gp, connected, 0, 0, discovered);

    for (i = 1; i < gp->num_v; i++)
    {
        if (connected[i] == i)
        {
            discovered[i] = 1;
            graph_ccRecursive(gp, connected, i, i, discovered);
        }
    }
    free(discovered);
    return connected;
}

void graph_ccRecursive(graph *gp, int* connected, int component_num, int starting_node, int* discovered)
{ // works kinda like DFS
    edge* temp = ((gp->adj_list)[starting_node])->next;

    while (temp != 0)
    {
        if(discovered[temp->vertex] == 0)
        {
            connected[temp->vertex] = component_num;
            discovered[temp->vertex] = 1;
            graph_ccRecursive(gp, connected, component_num, temp->vertex, discovered);
        }
        temp = temp->next;
    }
}

graph graph_collapse(graph *gp, int* connected)
{
    // collapses the nodes that are in the same CC into one single node

    int i, j, num_cc;
    num_cc = 0;
    int *new_connected = (int*) malloc(gp->num_v * sizeof(int));
    // counts the number of connected components
    for (i = 0; i < gp->num_v; i++)
    {
        if (connected[i] == i)
        {
            new_connected[i] = num_cc;
            num_cc++;
        }
    }
    for (i = 0; i < gp->num_v; i++)
    {
        new_connected[i] = new_connected[connected[i]];
    }

    // initialize all the weights in the new graph as invalid (-1)
    int *weight = (int*) malloc(num_cc * num_cc * sizeof(int));

    for (i = 0; i < num_cc; i++)
    {
        for (j = 0; j < num_cc; j++)
        {
            weight[i + num_cc * j] = -1;
        }
    }

    int a, b;
    for (i = 0; i < gp->num_v; i++)
    {
        edge* temp = ((gp->adj_list)[i])->next;
        while (temp != 0)
        {
            if (new_connected[temp->vertex] != new_connected[i])
            { // if this edge is not in the cc described by new_connected, it needs to be in the new graph
                a = new_connected[temp->vertex];
                b = new_connected[i];
                if ((weight[a + num_cc * b] == -1)||(weight[a + num_cc * b] > temp->cost))
                { // of all the edges between a and b, the smaller one will be the one to be inserted in the new graph
                    weight[a + num_cc * b] = temp->cost;
                }
            }
            temp = temp->next;
        }
    }

    graph new_graph = graph_create(num_cc);
    for (i = 1; i < num_cc; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (weight[i + num_cc * j] != -1)
            {
                graph_addEdge(&new_graph, i, j, weight[i + num_cc * j]);
            }
        }
    }

    free(weight);
	free(new_connected);

    return new_graph;
}

void graph_deleteGraph(graph* gp)
{
    edge *temp, *temp2;
    int i;
    for (i = 0; i < gp->num_v; i++)
    {
        temp = (gp->adj_list)[i];
        while (temp != 0)
        {
            temp2 = temp;
            temp = temp->next;
            free(temp2);
        }
    }
    free(gp->adj_list);
}

int graph_findBottleneckEdge(graph* gp)
{
    return graph_findBERecursive(gp);
}

int graph_isConnected(graph* gp, int *connected)
{
    int i;
    for (i = 1; i < gp->num_v; i++)
    { // if the graph is connected, all the nodes are in CC 0
        if (connected[i] == i)
        {
            return 0;
        }
    }
    return 1;
}

int graph_findBERecursive(graph* gp)
{

    edge_array *weights = graph_getWeights(gp);
    int median = selectElement(weights->array_pointer, weights->array_size, weights->array_size / 2);

    graph *new_gp = (graph*) malloc(sizeof(graph));

    *new_gp = graph_duplicateGraph(gp);

    /*  -------------------------------------------  */
    // the motivation for the following code is rather complicated, so
    // we explain it here. if we remove the edges greater than the median, then, if there's no
    // edge greater then the median, we end up not removing any edges. if we remove the
    // edges greater or equal to the median, then we risk removing all the edges, as it's
    // also possible that there's no edge smaller then the median. therefore, we need to check if
    // there is a smaller edge than the median. if that's the case, we can also remove all the edges
    // equal to the median. otherwise, we leave the edges equal to the median in the graph,
    // so we do not end with and edgeless graph.

	// we need to call graph_getWeights again because the 
	// function selectElement frees the vector from the heap
	free(weights);
	weights = graph_getWeights(gp);
	
    int i;
    int median_is_the_smaller_edge = 1;
    for (i = 0; i < weights->array_size; i++)
    {
        if (weights->array_pointer[i] < median)
        {
            median_is_the_smaller_edge = 0;
            break;
        }
    }
    if (median_is_the_smaller_edge)
    {
        graph_removeGreaterThen(new_gp, median);
    }
    else
    {
        graph_removeGreaterThenOrEqual(new_gp, median);
    }

    /*  -------------------------------------------  */
	
    free(weights->array_pointer);
    free(weights);
	
    int *connected = graph_getConnectedComponents(new_gp);
    int is_connected = graph_isConnected(new_gp, connected);

    if (is_connected)
    {
        graph_deleteGraph(gp);
        free(gp);
		free(connected);
        return graph_findBERecursive(new_gp);
    }
    else
    {
        graph_deleteGraph(new_gp);
        *new_gp = graph_collapse(gp, connected);
        graph_deleteGraph(gp);
        free(gp);
		free(connected);
        if (new_gp->num_v > 2)
        {
            return graph_findBERecursive(new_gp);
        }
        else
        {
            int b_edge = (((new_gp->adj_list)[0])->next)->cost;
            graph_deleteGraph(new_gp);
            free(new_gp);
            return b_edge;
        }
    }
}
