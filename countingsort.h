#ifndef COUNsize_tINGSORsize_t_H
#define COUNsize_tINGSORsize_t_H

#include "sort_controls.h"

//count sort works exceedingly well for arrays that hold
//duplicates of values

void countingsort(int* &arr, const size_t s);

int c_get_max(int* arr, const size_t s);

void countingsort(int* &arr, const size_t s){
    int max = c_get_max(arr, s);
    size_t* count = new size_t[max+1]; //doing this allows it to exceed 1mil
    int* temp = new int[s];

    for(size_t i = 0; i < max+1; i++)
        count[i] = 0;
    for(size_t i = 0; i < s; i++){
        count[arr[i]]++;
    }
    for(size_t i = 1; i < max+1; i++){
        count[i] += count[i-1];
    }
    for(size_t i = 0; i < s; i++){
        temp[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    delete[] arr;
    delete[] count;
    arr = temp;
    assert(verify_inc(arr, s));
}

int c_get_max(int *arr, const size_t s){
    int max = 0;
    for(size_t i = 0; i < s; i++)
        if(arr[i] > max)
            max = arr[i];
    return max;
}
#endif // COUNsize_tINGSORsize_t_H
