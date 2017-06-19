#ifndef DS_H
#define DS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEVEL 10
#define NUMNODES 1024

extern char *position[39];
extern char *company[26];


struct bin_tree {
	int data;
	int work_hours;
	int id;
  	char name[200];
	struct bin_tree * right, * left;
};

typedef struct bin_tree tree;
// THAT WOULD BE A GOOD RESULTS ARRAY
int top_work_hours[NUMNODES];
extern int g_node_id;

#endif
