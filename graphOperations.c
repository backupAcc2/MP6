/*
 * MP6 - graphOperations.c
 * Heath Gerrald
 * Fall 2018
 */

#include "graphOperations.h"
extern int graph_type;



/******************************************************************************
 * Function construct Graph
 * Creates our graph, dynamically allocates space for adjacency matrix
 * If graph_type is 1, creates graph given in MP6 pdf

 */
graph_t constructGraph(int vertices)
{
    graph_t G;
    double **matrix = (double **) malloc(vertices * sizeof(double *));
    for (int i = 0; i < vertices; i++)
     {
        matrix[i] = (double *) malloc(vertices * sizeof(double));
        for (int j = 0; j < vertices; j++)
            matrix[i][j] = FLT_MAX;
      }

    G.NumVertices = vertices;
    G.adjMatrix = matrix;

    if (graph_type == 1)
    {
        matrix[1][2] = 3;
        matrix[1][6] = 5;
        matrix[2][3] = 7;
        matrix[2][4] = 3;
        matrix[2][6] = 10;
        matrix[3][4] = 5;
        matrix[3][5] = 1;
        matrix[4][5] = 6;
        matrix[5][6] = 7;
        matrix[6][0] = 4;
        matrix[6][3] = 8;
        matrix[6][4] = 9;

    }



    return G;
}


/*void graph_add_edge(graph_t G, int link_scr, int link_dest, int link_weight)
{

}
*/

/******************************************************************************
 * Function destructGraph
 * frees memory in our adjacency matrix
 */
void destructGraph(graph_t *G){

}
