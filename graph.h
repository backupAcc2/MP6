/*
 * graphOperations.h
 * Heath Gerrald
 * MP6
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <float.h>

/* constants used with Global variables */
#define TRUE 1
#define FALSE 0

typedef struct {
  int NumVertices;
  double **adjMatrix;
} graph_t;

typedef struct {
  int predecessor;
  double cost;
} dijkstra_node;


graph_t constructGraph(int vertices);
void destructGraph(graph_t *G);
void graphOperation(graph_t *G, int operation);
void graph_debug_print(graph_t *G);
void print_adjMatrix(graph_t* G);

//void graph_add_edge(graph_t G, int link_scr, int link_dest, int link_weight);
