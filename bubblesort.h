//bubblesort -*- C++ -*-

//Copyright (C) 2018-2018 Stephen Crane and Co

//This file is part of the sorting algorithm library.
//I hereby grant any one who loves my code to use, redistribute, and/or
//modify my code for personal or commercial use under the
//Stephen Is Best General LIcense as published by Stephen Crane.

//No guarantees though.

/** @file include/bubblesort
 * Standard C++ header
 */
#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <cassert>
#include "sort_controls.h"

//SIGNATURES
template<class T>
void bubblesort(T* arr, const size_t& size);


//DEFINITIONS
template<class T>
void bubblesort(T* arr, const size_t& size){
    bool sorted_flag = false;
    while(!sorted_flag){
        sorted_flag = true; //if it ends with no swap, then it's sorted
        for(size_t i = 0; i < size-1; i++){
            if(arr[i] > arr[i+1]){
                swap(arr[i], arr[i+1]);
                sorted_flag = false;
            }
        }
    }
    assert(verify_inc(arr, size));
}

#endif // BUBBLESORT_H
