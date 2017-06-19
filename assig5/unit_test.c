#include "ds.h"
#include "companytree.h"
#include "companytree_ref.h"
#include "vis.h"

int main()
{
  int ind, failed=0;
  int top_work_hours_ref[NUMNODES];

  // run the sequential version
  printf("running reference sequential code\n"); 
  tree *node_ref = malloc(sizeof(tree));
  initialize(node_ref);
  traverse_ref(node_ref);
  tearDown(node_ref);

  for (ind = 0; ind < NUMNODES; ind++){
    top_work_hours_ref[ind]=top_work_hours[ind];
    top_work_hours[ind]=0;
  }
	
  printf("running the parallel code\n"); 
  
  // run the parallel version
  for(int i=16;i<32;i+=8){
    printf("with %d threads\n",i); 

    tree *node = malloc(sizeof(tree));
    initialize(node);
    traverse(node, i);
    tearDown(node);

    for (ind=0; ind<NUMNODES; ind++){
      if (top_work_hours_ref[ind]!=top_work_hours[ind]){
        failed=1;
        break;
      }
    }

    if (failed == 1){
      fprintf(stderr, "Wrong parallel result for %d: %s -> %d (correct: %d)\n",
                                ind, position[ind], top_work_hours[ind], top_work_hours_ref[ind]);
      printf("YOUR CODE FAILED THE UNIT TEST\n");
      break;
    } else {
      printf("YOUR CODE PASSED THE UNIT TEST\n");
    }
  }
}

