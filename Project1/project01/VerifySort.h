/*
 * File:   VerifySort.h
 * Author: scherrda
 * Section 1
 * Created on January 21, 2014, 3:00 PM
 */

#ifndef _VERIFYSORT_H_
#define _VERIFYSORT_H_
#include <vector>
using namespace std;

bool verifySort(vector<int> &x){
    for (int i = 0; i < x.size(); i++)
        if (x[i] < x[i-1])
            return false;
    return true;
}
#endif