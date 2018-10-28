//heapsort -*- C++ -*-

//Copyright (C) 2018-2018 Stephen Crane and Co

//This file is part of the sorting algorithm library.
//I hereby grant any one who loves my code to use, redistribute, and/or
//modify my code for personal or commercial use under the
//Stephen Is Best General LIcense as published by Stephen Crane.

//No guarantees though.

/** @file include/heapsort
 * Standard C++ header
 */
#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "sort_controls.h"

template<class T>
void heapsort(T* arr, const size_t& size);
template<class T> //orders it so the array represents a heap tree
void heaporder_simple(T* arr, const size_t& size);
template<class T>
void heapify_simple(T* arr, const size_t& size);
template<class T>//moves the small child that was put at root to bottom again
void reheapify(T* arr, const size_t& child, const size_t& size);
size_t get_parent(const size_t& i);
template<class T>
size_t get_child(T* arr, const size_t& s, const size_t& i);
template<class T>
bool verify_heap(T* arr, const size_t& s, const size_t& i);

template<class T>
void heapsort(T* arr, const size_t& size){
    //Uses nlogn time and constant space complexity
    //Let's turn the array into a heap!
    heaporder_simple(arr, size);
    //now let's swap the roots to the end of the array to begin the sorting process
    for(size_t i = 0; i < size; i++){
        swap(arr[0], arr[size - 1 - i]);
        //now we need to reheapify by moving this small root back in order
        reheapify(arr, 0, size - 1 - i);
    }
    assert(verify_inc(arr, size));
}
template< class T>
void heaporder_simple(T* arr, const size_t& size){
    //turns an array into a heap by starting with an empty heap and going one
    // at a time
    size_t heap_size = 0;

    for(size_t i = 0; i < size; i++){
        //add to the heap array from the current array
        heap_size++;
        //the total array is composed of two subarrays:
        //  left: {heap_array of length heap_size}
        //  right: {original array of length size-heap_size}
        heapify_simple(arr, heap_size);
    }
}
template<class T>
void heapify_simple(T* arr, const size_t& size){
    size_t new_i = size-1; //start at the last index
    size_t parent_i = get_parent(new_i);
    if(parent_i >= 0){
        if(arr[new_i] > arr[parent_i]){
            swap(arr[new_i], arr[parent_i]);
            new_i = parent_i;
            heapify_simple(arr, new_i+1); //recursive call
        }
    }
}
template<class T>
void reheapify(T* arr, const size_t& child, const size_t& size){
    size_t child_n = get_child(arr, size, child);
    if(child_n > 0 && arr[child] < arr[child_n]){
        swap(arr[child], arr[child_n]);
        reheapify(arr, child_n, size);
    }
}
size_t get_parent(const size_t& i){
    //parent index of the given index
    return (i-1)/2;
}
template<class T>
size_t get_child(T* arr, const size_t& s, const size_t& i){
    //returns index of larger child
    // or if there are no children,r eturn 0 (0 indicates an impossible child)
    if(2*i + 1 < s){
        if(2*i + 2 < s){
            return ((arr[2*i + 1] > arr[2*i + 2]) ? (2*i + 1) : (2*i + 2));
        }
        return 2*i + 1;
    }
    return 0;

}
template<class T>
bool verify_heap(T* arr, const size_t& s, const size_t& i){
    if(i >= s) //verify this is a heap
        return true;
    if(verify_heap(arr, s, 2*i+1) && verify_heap(arr, s, 2*i + 2)){
        if(i==0) //0 has no parent so just return true if all recursive calls were true!
            return true;
        else if(arr[i] <= arr[(i-1)/2])
            return true;
        else return false;
    }else return false;
}

#endif // HEAPSORT_H
