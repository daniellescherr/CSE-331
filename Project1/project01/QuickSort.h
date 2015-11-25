
/*
 * File:   QuickSort.h
 * Author: scherrda
 * Section 1
 * Created on January 21, 2014, 2:59 PM
 */

#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_
#include <vector>
#include "InsertionSort.h"
using namespace std;

void quickSort(vector<int> &x, int left = 0, int right = -2) {
    int pivot = x[right], geBegin;
    if (right == -2)
        right = x.size() - 1;
    if (left < right) {        pivot = x[right];
        geBegin = left;
        for (int i = left; i < right; i++)
            if (x[i] < pivot){
                swap(x[geBegin], x[i]);
                geBegin ++;
            }
        swap(x[right], x[geBegin]);
        quickSort(x, left, geBegin -1);
        quickSort(x, geBegin + 1, right);
    }
}
#endif