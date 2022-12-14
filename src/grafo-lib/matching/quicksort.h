#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "maximumMatching.h"

void swap(Vertex* x, Vertex* y);
int partition(Vertex* array, int p, int r);
void quicksort(Vertex* array, int p, int r);
#endif
