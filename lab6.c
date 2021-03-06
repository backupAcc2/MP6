/*
 * lab6.c
 * Heath Gerrald
 * MP6

 * Flags:
    -g [1|2|3] graph type, 1 = weakly-connected,
                           2 = strongly connected,
                           3 = random
    -n         N vertices in graph
    -a         Approximate number of adjacent vertices(R): 0 < R < N
    -h [1|2|3] Graph operation; 1 = shortest path
                                2 = Network diameter
                                3 = Multiple link-disjoint paths
    -s         Number of the source vertex 0 <= S < N
    -d         Number of the destination vertex 0 <= D < N
    -v         enable verbose output
    -r [x]     seed for the uniform random number generator
 */
#include "graph.h"

/* Global variables for command line parameters */
int graph_type = 0;
int seed = 10212018;
int Verbose = FALSE;
int vertices = 0;
int adjVerts = 0;
int graph_operation = 0;
int destination_vertex = 0;
int source_vertex = 0;

/* Prototypes for functions in this file only */
void getCommandLine(int argc, char **argv);


int main(int argc, char **argv)
{
  getCommandLine(argc, argv);
  graph_t G = constructGraph(vertices, adjVerts);

  clock_t start, end;
  double elapse_time; // time in milliseconds
  start = clock();
  graphOperation(&G, graph_operation);
  end = clock();
  elapse_time = 1000.0 * ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("elapse time: %lf\n", elapse_time);

  destructGraph(&G);

  return 0;
}


/******************************************************************************
 * Read in the command line arguments
 */
void getCommandLine(int argc, char **argv){
   int c;
   int index;

   while ((c = getopt(argc, argv, "g:n:a:h:s:d:vr:")) != -1)
      switch(c) {
        case 'g': graph_type = atoi(optarg);          break;
        case 'n': vertices = atoi(optarg);            break;
        case 'a': adjVerts = atoi(optarg);            break;
        case 'h': graph_operation = atoi(optarg);     break;
        case 's': source_vertex = atoi(optarg);       break;
        case 'd': destination_vertex = atoi(optarg);  break;
        case 'v': Verbose = TRUE;                     break;
        case 'r': seed = atoi(optarg);                break;

        default:
          puts("Lab 6 command line options");
          puts("   -g {1,2,3}  select graph type");
          puts("   -n          N vertices in graph");
          puts("   -a          Approximate nymber of adjacent vertices 0 < A < N");
          puts("   -h [1|2|3] Graph operation; 1 = shortest path");
          puts("                      2 = Network diameter");
          puts("                      3 = Multiple link-disjoint paths");
          puts("   -s          Number of the source vertex 0 <= S <= N");
          puts("   -d         Number of the destination vertex 0 <= D < N");
          puts("   -v         enable verbose output");
          puts("   -r [x]     seed for the uniform random number generator");
          exit(1);
      }

    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

}
