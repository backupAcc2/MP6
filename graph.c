/*
 * MP6 - graphOperations.c
 * Heath Gerrald
 * Fall 2018
 */

#include "graph.h"
extern int graph_type;
extern int source_vertex;
extern int destination_vertex;


/******************************************************************************
 * Function construct Graph
 * Creates our graph, dynamically allocates space for adjacency matrix
 * If graph_type is 1, creates graph given in MP6 pdf
 * If graph_type is 2, creates a strongly connected graph
 */
graph_t constructGraph(int vertices, int adjVerts)
{
    graph_t G;

    if (graph_type == 1) { G = create_graph_1(); }
    else if (graph_type == 2) {  G = create_graph_2(vertices); }
    else if(graph_type == 3) { G = create_graph_3(vertices, adjVerts); }

    return G;
}


/******************************************************************************
 * Function create_graph_1
 * Creates the weakly connected graph illustrated in the MP6 pdf
 */
graph_t create_graph_1()
{
  graph_t G;
  int vertices = 7;
  double **matrix = (double **) malloc(vertices * sizeof(double *));

  for (int i = 0; i < vertices; i++)
   {
      matrix[i] = (double *) malloc(vertices * sizeof(double));
      for (int j = 0; j < vertices; j++)
      {
         if (i == j) { matrix[i][j] = 0; }
         else { matrix[i][j] = FLT_MAX; }
      }
   }

    G.NumVertices = vertices;
    G.adjMatrix = matrix;

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

  return G;
}

/******************************************************************************
 * Funciton create_graph_2
 * Creates the strongly connected graph from the pdf for MP6
 * Parameter 'vertices' is inputted from -n flag
 */
graph_t create_graph_2(int vertices)
{
   graph_t G;
   double **matrix = (double **) malloc(vertices * sizeof(double *));
   for (int i = 0; i < vertices; i++)
   {
      matrix[i] = (double *) malloc(vertices * sizeof(double));
      for (int j = 0; j < vertices; j++)
      {
        if (i == j) { matrix[i][j] = 0; }
        else { matrix[i][j] = (abs(i-j) + pow(i-j+2, 2) + 3*j); }
      }
   }

   G.NumVertices = vertices;
   G.adjMatrix = matrix;

   return G;

}


/******************************************************************************
 * Function create_graph_3()
 * Creates the random graph with -n vertices and -a adjacent vertices
 */
graph_t create_graph_3(int vertices, int adjNeighbors)
{
    graph_t G;
    int i, j, adj_count;
    int min = vertices;
    int max = 0;
    int max_vertex, min_vertex;
    double total_adj_count = 0.0;
    double C, M, D, F;

  // adjacency matrix, holds the cost to get to each node from each vertex
    double **matrix = (double **) malloc(vertices * sizeof(double *));
    double matrix_x[vertices]; // holds the x values of each vertex
    double matrix_y[vertices]; // holds the y values of each vertex

  // find our value of C
    C = sqrt(adjNeighbors / (vertices * M_PI));

  // find our value of M
    M = log10(1 + pow(1/C, 2));

  // find the x and y coordinates of each vertex
    for (i = 0; i < vertices; i++)
    {
      if (i == 0) {matrix_x[i] = 0.0; matrix_y[i] = 0.5;}
      else if (i == vertices-1) {matrix_x[i] = 1.0; matrix_y[i] = 0.5;}
      else
      {
          matrix_x[i] = drand48();
          matrix_y[i] = drand48();
      }
    }

  // fill in the adjacency matrix
    for(i =0; i < vertices; i++)
    {
        adj_count = 0;
        matrix[i] = (double *) malloc(vertices * sizeof(double));
        for (j = 0; j < vertices; j++)
        {
            D = sqrt(pow(matrix_x[i] - matrix_x[j], 2) + pow(matrix_y[i] - matrix_y[j],2));
            if (i == j) {matrix[i][j] = 0;}
            else if ( D <= C)
            {
                F = log10(1+pow(1/(D + C/1000), 2));
                matrix[i][j] = M / F;
                adj_count++;
                total_adj_count++;
            }

            else {matrix[i][j] = FLT_MAX;}
        }
        if (adj_count < min) {min = adj_count; min_vertex = i;}
        if (adj_count > max) {max = adj_count; max_vertex = i;}
    }


    G.adjMatrix = matrix;
    G.NumVertices = vertices;

    // print out the necessarry statistics
    // average, max, and min number of adjacent vertices
    printf("Average number of ajacent vertices: %.2lf\n", total_adj_count / vertices);
    printf("Maximum adjacent vertices of a vertex: %d (vertex %d)\n", max, max_vertex);
    printf("Minimum adjacent vertices of a vertex: %d (vertex %d)\n", min, min_vertex);

    return G;
}

/******************************************************************************
 * Function destructGraph
 * frees memory in our adjacency matrix
 */
void destructGraph(graph_t *G)
{
    int vertices = G->NumVertices;
    for(int i = 0; i < vertices; i++){
      free(G->adjMatrix[i]);
    //  free(G->adjMatrix[i]);
    }
  free(G->adjMatrix);

}

/******************************************************************************
 * Function graphOperations
 * Used with the -h flag, runs operation 1, 2, or 3
 */
void graphOperation(graph_t *G, int operation)
{
    if (operation == 1) // finding shortest path from source_vertex to destination_vertex
      {
        double distances[G->NumVertices];
        shortestPath(G, distances, source_vertex, destination_vertex, 1);
       }

    else if (operation == 2)
      {  network_diameter(G); }
}


/******************************************************************************
 * Function shortestPath
 * Called if graph_operation == 1
 * Finds the shortest path from source to destination and prints the cost and path
 * distance_array is the array which holds the costs from the source to each vertice
 */
void shortestPath(graph_t *G, double distance_array[], int source, int destination, int print)
{
       int vertices = G->NumVertices;
       double MinDistance = FLT_MAX;
       int vertex_w, i;
       double path_cost;
       int confirmed_count = 0;
       int no_new_paths = FALSE;

       // the following is a set containing the vertices for which we have
       // confirmed the shortest distance. 1 means yes, 0 means no
       int *confirmed = (int*) calloc(vertices, sizeof(int));
       confirmed[source] = 1;
       confirmed_count++;

       // an array containing the predecessor to reach each vertex
       int predecessor_array[vertices];

     // fill in the shortestDistance array with the distances from the source
     // predecessors for each will start as source
       for (i = 0; i < vertices; i++)
          {
            distance_array[i] = G->adjMatrix[source][i];
            predecessor_array[i] = source;
          }
         predecessor_array[source] = -1;

       while(confirmed_count != vertices && no_new_paths == FALSE)
       {
           MinDistance = FLT_MAX;
           vertex_w = -1; // invalid vertex, for now

         // find the vertex at the minimum distance from the source
           for (i = 0; i < vertices; i++)
           {
             if (confirmed[i] == 0 && distance_array[i] < MinDistance)
             {
               MinDistance = distance_array[i];
               vertex_w = i;
             }
           }

         // if no vertex was found, there are no new paths
         if (vertex_w == -1) { no_new_paths = TRUE; }

         else
         {
            // if a vertex was found, add vertex_w to confirmed set
              confirmed[vertex_w] = 1;
              confirmed_count++;

            // update the shortest distances via vertex_w that are not already confirmed
            for (i = 0; i < vertices; i++)
            {
              if (G->adjMatrix[vertex_w][i] < FLT_MAX && confirmed[i] == 0)
              {
                  path_cost = distance_array[vertex_w] + G->adjMatrix[vertex_w][i];
                  if (path_cost < distance_array[i])
                   {
                      distance_array[i] = path_cost;
                      predecessor_array[i] = vertex_w;
                   }
              }

            }

         } // closes 'else'
       } // closes while loop


       if (print == TRUE)
       {
         // print out the path cost
         printf("Cost from source to destination: ");
         if (distance_array[destination] == FLT_MAX)
            { printf("No path exists\n"); }
         else
            printf("%0.2lf\n", distance_array[destination]);

    // print out the shortest path from source to destination
         if (distance_array[destination] != FLT_MAX)
         {
             // we need to print the shortest path in correct order, not starting
             // from the predecessor and ending at the souce
             i = destination;
             int path_count = 0;
             while (i >= 0)
                { path_count++; i = predecessor_array[i];  }

             int temp = path_count - 2; // -2 since path_count -1 is destination
             // and we are filling the array starting at the destination predecessor

             int create_path[path_count];
             create_path[path_count - 1] = destination;
             i = destination;
             while (temp >= 0)
                {  create_path[temp] = predecessor_array[i];
                   i = predecessor_array[i];
                   temp--;
                }

             printf("Shortest path from source to destination: %d ", source);
             for (i = 1; i < path_count; i++)
             {
               printf("--> %d ", create_path[i]);
             }
             puts("");
         }
      } // closes 'if print == TRUE'

     // free confirmed
     free(confirmed);

}

/*
 * Function network_diameter()
 * Finds the longest possible path between vertices in the graph for which there
 *   is a path
 * Prints the path and the two vertices which have the greatest distance
 */
void network_diameter(graph_t *G)
{
    int num_vertices = G->NumVertices;
    int no_path_count = 0;
    double max_cost = 0;
    int max_source, max_destination;
    double distances[num_vertices][num_vertices];

    for (int i = 0; i < num_vertices; i++)
    {
        shortestPath(G, distances[i], i, i, FALSE);
        for (int j = 0; j < num_vertices; j++)
        {
          if (distances[i][j] > max_cost && distances[i][j] < FLT_MAX)
          {
                max_cost = distances[i][j];
                max_destination = j;
                max_source = i;
          }
          if (distances[i][j] == FLT_MAX)
                no_path_count++;
        }
    }

    printf("The network diameter is %0.3lf\n", max_cost);
    if (no_path_count > 0)
        puts("The graph contains at least one pair of vertices with no path");

    shortestPath(G, distances[0], max_source, max_destination, TRUE);

}

/******************************************************************************
 * Function printGraph
 * Prints a visual representation of the graph
 */
void graph_debug_print(graph_t *G)
{
   for(int i = 0; i < G->NumVertices; i++)
   {
      printf("Adjacency list of vertex %d\n", i);
      printf("head: %d ->", i);
      for (int j = 0; j < G->NumVertices; j++)
      {
          if(G->adjMatrix[i][j] < FLT_MAX && i != j)
          {
              printf(" %d,", j);
          }
      }
      printf("\n\n"); // newline
   }
}

/******************************************************************************
 * Function print_adjMatrix
 * Prints the adjacency matrix of our graph
 */
void print_adjMatrix(graph_t *G)
{
  printf("Adjacency Matrix: \n");
   for (int i = 0; i < G->NumVertices; i++)
   {
     for (int j = 0; j < G->NumVertices; j++)
     {
        if(G->adjMatrix[i][j] == FLT_MAX)
          printf("   %*s   ", 6, "INF");
        else
          printf("   %0*.2lf   ", 6, G->adjMatrix[i][j]);
     }
     puts("");
   }
}
