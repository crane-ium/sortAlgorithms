//radixsort, v2 -*- C++ -*-

//Copyright (C) 2018-2018 Stephen Crane and Co

//This file is part of the sorting algorithm library.
//I hereby grant any one who loves my code to use, redistribute, and/or
//modify my code for personal or commercial use under the
//Stephen Is Best General LIcense as published by Stephen Crane.

//No guarantees though.

/** @file include/radixsort_two
 * Standard C++ header
 */
#ifndef RADIXSORT_TWO_H
#define RADIXSORT_TWO_H

#include "sort_controls.h"

//I wanted a better implementation of radix sort
//Also, want a radix sort that can use strings
template<class T>
T get_max(T* arr, const size_t s);
template<class T>
void count_sort(T* &arr, const size_t& s, const size_t exp);
template<class T>
void radixsort_two(T* &arr, const size_t s);

template<class T>
T get_max(T* arr, const size_t s){
    T max = T();
    for(size_t i = 0; i < s; i++){
        if(arr[i] > max)
            max = arr[i];
    }
    return max;
}
template<class T>
void count_sort(T* &arr, const size_t& s, const size_t exp){
    T* next_arr = new T[s];
//    T next_arr[s];
    size_t count[10]={0}; //counting the number of digits
    size_t i;
    for(i = 0; i < s; i++)
        count[arr[i]/exp%10]++;
    for(i = 1; i < 10; i++)
        count[i] += count[i-1];
    for(i = 0; i < s; i++){
        size_t index = arr[s-i-1]/exp % 10;
        next_arr[count[index] - 1] = arr[s-i-1];
        count[index]--;
    }
    //Is it better to delete the old array and just set new array?
    //or to copy index by index into the old array?
    delete[] arr;
    arr = next_arr;
    //ANSER: deleting and replacing is about 20% faster
//    for(i = 0; i < s; i++)
//        arr[i] = next_arr[i];
//    delete[]  next_arr;
}
template<class T>
void radixsort_two(T* &arr, const size_t s){
    T max = get_max(arr, s);
    for(size_t i = 1; max/i > 0; i*=10){
        count_sort(arr, s, i);
    }
    //verify inc
    assert(verify_inc(arr, s));
}

#endif // RADIXSORT_TWO_H
