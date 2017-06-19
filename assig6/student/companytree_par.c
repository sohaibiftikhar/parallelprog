#include "companytree.h"
#include <omp.h>
#define NEST_LIMIT 7

void traverse_par(tree *node,  int itrNo) {
    if (node != NULL) {
		node->work_hours = compute_workHours(node->data);
		top_work_hours[node->id] = node->work_hours;
		
		//potential tasks and sessions will take place here
        #pragma omp task shared(node) final (itrNo > NEST_LIMIT)
		traverse_par(node->right,  itrNo + 1);
        #pragma omp task shared(node) final (itrNo > NEST_LIMIT)
		traverse_par(node->left, itrNo + 1);
        
        #pragma omp taskwait
        
	}
}

void traverse(tree *node, int numThreads){
    //write your parallel solution here
    omp_set_num_threads(numThreads);
    #pragma omp parallel shared(node) 
    {
        #pragma omp single
        traverse_par(node, 1);
    }
}

