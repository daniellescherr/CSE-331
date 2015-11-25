/*
 * File:   InsertionSort.h
 * Author: scherrda
 * Section 1
 * Created on January 21, 2014, 2:59 PM
 */

#ifndef _INSERTIONSORT_H_
#define _INSERTIONSORT_H_
#include <vector>
using namespace std;

void insertionSort(vector<int> &x){
    for (int i = 1; i<x.size(); i++){
        int j = i;
        while ((j > 0) && (x[j-1]>x[j])){
            swap (x[j], x[j-1]);
            j--;
        }
    }
}
#endif



