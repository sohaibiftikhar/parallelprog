#include "companytree_ref.h"

void traverse_ref(tree *node){

	if(node != NULL){
		node->work_hours = compute_workHours(node->data);
		top_work_hours[node->id] = node->work_hours;
		
		//potential tasks and sessions will take place here
		traverse_ref(node->right);
		traverse_ref(node->left);
	}
}

