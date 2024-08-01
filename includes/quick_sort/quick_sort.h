#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include <iostream>
#include <vector>
#include "../table/typedefs.h"

using namespace std;

void quick_sort(vectorlong& v);//for calling

void quick_sort(vectorlong& v, int start, int end);//for sorting

void partition(vectorlong& v, int start, int end, int& midIndex);//start->midIndex-1 < midIndex && midIndex < mid+1->end

void swap(vectorlong& v, int a, int b);

int get_first_biggest(vectorlong& v, int start, int end);//goes from start
int get_first_smallest(vectorlong& v, int start, int end);//goes from end

#endif