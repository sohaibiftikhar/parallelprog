#include "ds.h"
#include "companytree.h"
#include "vis.h"
#include "time.h"

// Use clock_gettime in linux, clock_get_time in OS X.
void get_monotonic_time(struct timespec *ts){
#ifdef __MACH__
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts->tv_sec = mts.tv_sec;
  ts->tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_MONOTONIC, ts);
#endif
}

int main(int argc, char** argv){
  long int num_threads = 4;
  struct timespec begin, end;

  // argument handling
  if (argc != 2) {
    fprintf(stderr, "usage: %s [#threads]\n", argv[0]);
    return 1;
  }
  if ((num_threads = strtol(argv[1], NULL, 0)) == 0 || num_threads < 0) {
    fprintf(stderr, "#threads not valid!\n");
    return 1;
  }

  // insert nodes (employee positions) in the company tree
  tree *topNode = malloc(sizeof(tree));
  initialize(topNode);


  // visit all of them to compute work hours in a mysterious way
  // clock_gettime(CLOCK_MONOTONIC, &begin);
  get_monotonic_time(&begin);
  traverse(topNode, num_threads);
  //clock_gettime(CLOCK_MONOTONIC, &end);
  get_monotonic_time(&end);
  // Showing results
  visualize();

  tearDown(topNode);
  
  // print timing information
  printf("\n\nTime: %.5f seconds\n", ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
                     ((double)begin.tv_sec + 1.0e-9*begin.tv_nsec));
  return 0;
}

