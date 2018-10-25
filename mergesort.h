//mergesort -*- C++ -*-

//Copyright (C) 2018-2018 Stephen Crane and Co

//This file is part of the sorting algorithm library.
//I hereby grant any one who loves my code to use, redistribute, and/or
//modify my code for personal or commercial use under the
//Stephen Is Best General LIcense as published by Stephen Crane.

//No guarantees though.

/** @file include/mergesort
 * Standard C++ header
 */

#ifndef MERGESORT_H
#define MERGESORT_H

#include <cassert>
#include <vector>
#include <functional>
#include "sort_controls.h"

//SIGNATURES
template<typename T>
void mergesort(T arr[], const size_t& size
             , bool ascending=true, bool absolute=false);
template<typename T> //function<T(T[], const size_t&, const size_t&)>
void merge(T arr[], size_t a, size_t b
         ,  sort_order<T>* order_func);


//DEFINITIONS
template<typename T>
void mergesort(T arr[], const size_t& size
               ,  bool ascending, bool absolute){
    /**
     * @brief mergesort sorts an array[size], in an order
     * @param arr: array portion to be merge sorted
     * @param size: length of arr interval
     * @param ascending=true: order to sort
     * @param absolute=false:  check that order is absolute or not
     */
    size_t  a   = size/2,
            b   = size - a; //intervals [0,a],[a+1,b]

    sort_order<T>* order = new sort_order<T>(ascending);

    cout << "TEST\n";
    if(a > 1) //merge the left array
            mergesort(arr, a, ascending, absolute);
    if(b > 1) //merge the right array
            mergesort((arr+a), b, ascending, absolute);

    merge(arr, a, b, order); //sort the two arrays
}

template<typename T>
/**
 * @brief merge
 * @param arr: full array
 * @param a: size of left arr partition
 * @param b: size of right arr partition
 * @param order_func: functor
 */
void merge(T arr[], size_t a, size_t b
           ,  sort_order<T> *order_func){
    size_t count_l=0, count_r=a;
    T temp[a+b];
    cout << "array segment over [" << count_l << ", " << count_r << "]" << endl;
    print_array_segment(arr, 0, a+b);
    cout << "countl: " << count_l << " countr: " << count_r << endl;
    while(count_l < a || count_r < a+b){
        if(count_l < a && count_r < a+b)
            temp[count_l + count_r - a] = (*order_func)(arr, count_l, count_r);
        else if(count_l < a){
            temp[count_l + count_r - a] = arr[count_l];
            count_l++;
        }else if(count_r < a+b){
            temp[count_r] = arr[count_r];
            count_r++;
        }
        cout << "countl: " << count_l << " countr: " << count_r << endl;
    }
    print_array_segment(temp, 0, a+b);
    for(size_t i = 0; i < (a+b); i++){
        arr[i] = temp[i];
    }
    delete[] temp;
    //verify order of arr
}
#endif // MERGESORT_H
