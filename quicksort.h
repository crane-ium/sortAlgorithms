//quicksort -*- C++ -*-

//Copyright (C) 2018-2018 Stephen Crane and Co

//This file is part of the sorting algorithm library.
//I hereby grant any one who loves my code to use, redistribute, and/or
//modify my code for personal or commercial use under the
//Stephen Is Best General LIcense as published by Stephen Crane.

//No guarantees though.

/** @file include/quicksort
 * Standard C++ header
 */
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "sort_controls.h"

template<class T>
void quicksort(T* arr, const size_t& size);
template<class T>
void quicksort_rec(T* arr, const size_t& size);
//template<class T>
//void quicksort_order(T* arr, const size_t& size, bool ascending=true);
template<class T>
void partition(T* arr, const size_t& s, size_t& p_i);

template<class T>
void quicksort(T* arr, const size_t& size){
    quicksort_rec(arr, size);
//    assert(verify_inc(arr, size));
}
template<class T>//recursive calls
void quicksort_rec(T* arr, const size_t& size){
    if(size > 1){
        size_t p_i;//pivot index
        partition(arr, size, p_i);
        quicksort_rec(arr, p_i);
        quicksort_rec((arr+p_i + 1), size - p_i - 1);
    }
}
template<class T>
void partition(T* arr, const size_t& s, size_t& p_i){
    size_t base_i = 0;//pivot is leftmost index
    T pivot = arr[base_i];
    size_t left_i = 1, right_i = s-1;

    //could be really bad time if the pivot is always the smallest
    while(left_i <= right_i){
        while(left_i < s && arr[left_i] <= pivot)
            left_i++;
        while(arr[right_i] > pivot)
            right_i--;
        if(left_i < right_i)
            swap(arr[left_i], arr[right_i]);
    }
    p_i = right_i;
    swap(arr[base_i], arr[p_i]);
}
//template<class T>
//void quicksort_order(T* arr, const size_t& size, bool ascending){

//}
//template<class T>
//void partition(T* arr, const size_t& s, size_t& p_i, bool asc=true){
//    //set the p_i (pivot index) to the updated index after partitioning
//    size_t base_i = 0;
//    T pivot = arr[base_i]; //let's start by setting the pivot as the first element
//    size_t left_i = 1, right_i = s-1;

//    while(left_i <= right_i){
//        while(left_i<s && sort_comp(arr[left_i], pivot, asc)){ //arr[left_i] <= pivot
//            left_i++;
//        }
//        while(sort_comp(pivot, arr[right_i], asc) && !(pivot==arr[right_i])){ //arr[right_i] > pivot
//            right_i--;
//        }
//        if(left_i < right_i){
//            swap(arr[left_i], arr[right_i]);
//        }
//    }
//    p_i = right_i;
//    swap(arr[base_i], arr[right_i]);

//}

#endif // QUICKSORT_H
