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

 */
graph_t constructGraph(int vertices)
{
    graph_t G;
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
    if (operation == 1)
    {
      // finding shortest path from source_vertex to destination_vertex

      int vertices = G->NumVertices;
      double MinDistance = FLT_MAX;
      int vertex_w;
      int i;
      double path_cost;
      int confirmed_count = 0;
      int no_new_paths = FALSE;

      // the following is a set containing the vertices for which we have
      // confirmed the shortest distance. 1 means yes, 0 means no
      int *confirmed = (int*) calloc(vertices, sizeof(int));
      confirmed[source_vertex] = 1;
      confirmed_count++;

      // an array containing the shortest distance from the source to each
      // vertex, each vertex represented by the index. Each dijskstra_node
      // contains the cost and the predecessor to get to that node
      dijkstra_node **shortestDistance = (dijkstra_node**)malloc(sizeof(dijkstra_node) * vertices);

    // fill in the shortestDistance array with the distances from the source
      for (i = 0; i < vertices; i++)
         {
           shortestDistance[i] = (dijkstra_node*)malloc(sizeof(dijkstra_node));
           shortestDistance[i]->cost = G->adjMatrix[source_vertex][i];
           shortestDistance[i]->predecessor = source_vertex;
         }
        shortestDistance[source_vertex]->predecessor = -1;

      while(confirmed_count != vertices && no_new_paths == FALSE)
      {
          MinDistance = FLT_MAX;
          vertex_w = -1; // invalid vertex, for now

        // find the vertex at the minimum distance from the source
          for (i = 0; i < vertices; i++)
          {
            if (confirmed[i] == 0 && shortestDistance[i]->cost < MinDistance)
            {
              MinDistance = shortestDistance[i]->cost;
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
                 path_cost = shortestDistance[vertex_w]->cost + G->adjMatrix[vertex_w][i];
                 if (path_cost < shortestDistance[i]->cost)
                  {
                     shortestDistance[i]->cost = path_cost;
                     shortestDistance[i]->predecessor = vertex_w;
                  }
             }

           }

        } // closes 'else'
      } // closes while loop

      // print out the path cost
      printf("Cost from source to destination: ");
      if (shortestDistance[destination_vertex]->cost == FLT_MAX)
         { printf("No path exists\n"); }
      else
         printf("%0.2lf\n", shortestDistance[destination_vertex]->cost);

      // print out the shortest path from source to destination
      if (shortestDistance[destination_vertex]->cost != FLT_MAX)
      {
          // we need to print the shortest path in correct order, not starting
          // from the predecessor and ending at the souce
          i = destination_vertex;
          int path_count = 0;
          while (i >= 0)
             { path_count++; i = shortestDistance[i]->predecessor;  }

          int temp = path_count - 2; // -2 since path_count -1 is destination_vertex
          // and we are starting at the destination predecessor

          int create_path[path_count];
          create_path[path_count - 1] = destination_vertex;
          i = destination_vertex;
          while (temp >= 0)
             {  create_path[temp] = shortestDistance[i]->predecessor;
                i = shortestDistance[i]->predecessor;
                temp--;
             }

          printf("Shortest path from source to destination: %d ", source_vertex);
          for (i = 1; i < path_count; i++)
          {
            printf("--> %d ", create_path[i]);
          }
          puts("");
      }

    } // closes if operation == 1
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
 * Prints the adjacency matrix of our graph
 */
void print_adjMatrix(graph_t *G)
{
   for (int i = 0; i < G->NumVertices; i++)
   {
     for (int j = 0; j < G->NumVertices; j++)
     {
        if(G->adjMatrix[i][j] == FLT_MAX)
          printf("   INF   ");
        else
          printf("   %0.1lf   ", G->adjMatrix[i][j]);
     }
     puts("");
   }
}
