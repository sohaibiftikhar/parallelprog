#include "companytree.h"
#include <omp.h>
#define NEST_LIMIT 5

void traverse_par(tree *node) {
    if (node != NULL) {
		node->work_hours = compute_workHours(node->data);
		top_work_hours[node->id] = node->work_hours;
		
		//potential tasks and sessions will take place here
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                traverse_par(node->right);
            }
            #pragma omp section
            {
		        traverse_par(node->left);
            }
        }
	}
}

void traverse(tree *node, int numThreads){
    //write your parallel solution here
    omp_set_num_threads(numThreads);
    omp_set_nested(1);
    omp_set_max_active_levels(NEST_LIMIT);
    traverse_par(node);
}

