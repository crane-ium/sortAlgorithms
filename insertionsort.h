//Copyright (C) 2018-2018 Stephen Crane and Co

//This file is part of the sorting algorithm library.
//I hereby grant any one who loves my code to use, redistribute, and/or
//modify my code for personal or commercial use under the
//Stephen Is Best General LIcense as published by Stephen Crane.

//No guarantees though.

/** @file include/insertionsort
 * Standard C++ header
 */
#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <cstdlib>
#include "sort_controls.h"

using namespace std;

template<class T>
/**
 * @brief insertionsort: sorts by moving elements of one
 *  unordered list into a new ordered list
 * @param arr
 * @param size
 */
void insertionsort(T* arr, const size_t& size);

template<class T>
void insertionsort(T* arr, const size_t& size){
    T temp;
    size_t n;
    for(size_t i = 0; i < size; i++){ //iterate through "right" array
        temp = arr[i];
        //iterate thru left array
        for(n = i; n > 0; n--){ //sort in ascending order
            if(temp < arr[n-1])
                swap(arr[n], arr[n-1]);
            else
                break;
        }
        arr[n] = temp; //"insert"
    }
    assert(verify_inc(arr, size));
}
#endif // INSERTIONSORT_H
