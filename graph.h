/*
 * graphOperations.h
 * Heath Gerrald
 * MP6
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>

/* constants used with Global variables */
#define TRUE 1
#define FALSE 0

typedef struct {
  int NumVertices;
  double **adjMatrix;
} graph_t;


graph_t constructGraph(int vertices, int adjVerts);
graph_t create_graph_1();
graph_t create_graph_2(int);
graph_t create_graph_3(int, int);
void destructGraph(graph_t *G);
void graphOperation(graph_t *G, int operation);
void shortestPath(graph_t *G, double[], int[], int source, int destination, int print);
void network_diameter(graph_t *G);
void link_disjoint_path(graph_t *G, int source, int destination);
void graph_debug_print(graph_t *G);
void print_adjMatrix(graph_t* G);
