/*
 * graphOperations.h
 * Heath Gerrald
 * MP6
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <float.h>


typedef struct {
  int NumVertices;
  double **adjMatrix;
} graph_t;


graph_t constructGraph(int vertices);
void destructGraph(graph_t *G);

//void graph_add_edge(graph_t G, int link_scr, int link_dest, int link_weight);
