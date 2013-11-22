#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <math.h>

int associativity = 2;          
int blocksize_bytes = 32;       
int cachesize_kb = 64;          
int miss_penalty = 30;

void
print_usage ()
{
  printf ("Usage: gunzip2 -c <tracefile> | ./cache -a assoc -l blksz -s size -mp mispen\n");
  printf ("  tracefile : The memory trace file\n");
  printf ("  -a assoc : The associativity of the cache\n");
  printf ("  -l blksz : The blocksize (in bytes) of the cache\n");
  printf ("  -s size : The size (in KB) of the cache\n");
  printf ("  -mp mispen: The miss penalty (in cycles) of a miss\n");
  exit (0);
}

int main(int argc, char * argv []) {

  long address;
  int loadstore, icount;
  char marker;
  
  int i = 0;
  int j = 1;
 
  while (j < argc) {
    if (strcmp ("-a", argv [j]) == 0) {
      j++;
      if (j >= argc)
        print_usage ();
      associativity = atoi (argv [j]);
      j++;
    } else if (strcmp ("-l", argv [j]) == 0) {
      j++;
      if (j >= argc)
        print_usage ();
      blocksize_bytes = atoi (argv [j]);
      j++;
    } else if (strcmp ("-s", argv [j]) == 0) {
      j++;
      if (j >= argc)
        print_usage ();
      cachesize_kb = atoi (argv [j]);
      j++;
    } else if (strcmp ("-mp", argv [j]) == 0) {
      j++;
      if (j >= argc)
        print_usage ();
      miss_penalty = atoi (argv [j]);
      j++;
    } else {
      print_usage ();
    }
  }

  
  printf("Cache parameters:\n");
  printf ("Cache Size (KB)\t\t\t%d\n", cachesize_kb);
  printf ("Cache Associativity\t\t%d\n", associativity);
  printf ("Cache Block Size (bytes)\t%d\n", blocksize_bytes);
  printf ("Miss penalty (cyc)\t\t%d\n",miss_penalty);
  printf ("\n");

  while (scanf("%c %d %lx %d\n",&marker,&loadstore,&address,&icount) != EOF) {
    
    if(i<10){
	printf("\t%c %d %lx %d\n",marker, loadstore, address, icount);
	i++;
    }
    else{
	return 1;
    }

   

  }
  

  printf("Simulation results:\n");
  
  
  /*
 *   printf("\texecution time %ld cycles\n", ?);
 *     printf("\tinstructions %ld\n", ?);
 *       printf("\tmemory accesses %ld\n", ?);
 *         printf("\toverall miss rate %.2f\n", ? );
 *           printf("\tread miss rate %.2f\n", ? );
 *             printf("\tmemory CPI %.2f\n", ?);
 *               printf("\ttotal CPI %.2f\n", ?);
 *                 printf("\taverage memory access time %.2f cycles\n",  ?);
 *                   printf("dirty evictions %d\n", ?);
 *                     printf("load_misses %d\n", ?);
 *                       printf("store_misses %d\n", ?);
 *                         printf("load_hits %d\n", ?);
 *                           printf("store_hits %d\n", ?);
 *                             */

}

