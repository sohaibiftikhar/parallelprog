#ifndef FT_H
#define FT_H

#include "ds.h"

void fill(tree* node, int level);
void initialize(tree* node);
void tearDown(tree* node);
int compute_workHours(int data);
void traverse(tree *node, int numThreads);

#endif
