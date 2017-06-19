#include "companytree.h"

void traverse(tree *node, int numThreads){

	if(node != NULL){
		node->work_hours = compute_workHours(node->data);
		top_work_hours[node->id] = node->work_hours;
		
		traverse(node->right, numThreads);
		traverse(node->left, numThreads);
	}
}

