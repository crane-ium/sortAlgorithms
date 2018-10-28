//bucketsort -*- C++ -*-

//Copyright (C) 2018-2018 Stephen Crane and Co

//This file is part of the sorting algorithm library.
//I hereby grant any one who loves my code to use, redistribute, and/or
//modify my code for personal or commercial use under the
//Stephen Is Best General LIcense as published by Stephen Crane.

//No guarantees though.

/** @file include/bucketsort
 * Standard C++ header
 */
#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include "sort_controls.h"
#include <vector>

//I predict bucketsort to be fastest since it works well with
// even distribution models in O(kn) time
template<class T>
/**
 * @brief bucketsort: also known as bin sort, uses a pigeonhole property
 *          -This bucket sort version only sorts 0 and positive integers
 * @param arr: array to be sorted
 * @param size: size of array
 */
void bucketsort(T* arr, const size_t& size);
template<class T>
void add_buckets(vector<vector<T> >& v, const size_t& b_count, const size_t& b_new);
template<class T>
void bucket_insert(vector<vector<T> >& v, const size_t& i, const T& e);


template<class T>
void bucketsort(T* arr, const size_t& size){
    //we will use vectors (dynamic arrays) to prevent having to allocate
    // size*k elements, giving us O(size*k) space complexity. k is number
    // of buckets. We can try both methods and compare time.
    vector<vector<T> > buckets;
    size_t b_count = 0; //count of how many buckets there currently are
    //let's set a constant for expected average bucket size. We can tamper later
    static const size_t b_size = 230;
    for(size_t i = 0; i < size; i++){
        //add element by element to their respective buckets
        if((int)(buckets.size()*b_size) - 1 < arr[i])
            add_buckets(buckets, b_count, arr[i]/b_size+1);
//        buckets[arr[i]/b_size].push_back(arr[i]);
        bucket_insert(buckets, arr[i]/b_size, arr[i]);
//        for(size_t ii = 0; i < buckets[0].size(); ii++)
//            cout << buckets[0][ii] << " ";
//        cout << endl;
    }
    //done adding them all into buckets, now we readd them back to array
    size_t count = 0; //number of buckets emptied
    for(size_t i = 0; i < size; i++){
        while(buckets[count].size() == 0)
            count++;
        arr[i] = buckets[count][buckets[count].size()-1]; //buckets are in reverse order
        buckets[count].pop_back();
    }
    assert(verify_inc(arr, size));
}
template<class T>
void add_buckets(vector<vector<T> >& v, const size_t& b_count, const size_t& b_new){
    //b_new: how many buckets there need to be total
    if(b_count >= b_new)
        return;
    for(size_t i = b_count; i < b_new; i++){
        v.push_back(vector<T>());
    }
}
template<class T>
void bucket_insert(vector<vector<T> >& v, const size_t& i, const T& e){
    //insert like an insertion sort
    if(v[i].size() == 0)
        v[i].push_back(e);
    typename vector<T>::iterator it;
    for(it = v[i].begin(); it != v[i].end(); it++)
        if(e > (*it)) //we do more comparisons but we move the array less!
            break;
    if(e>(*it))
        v[i].insert(it, e);
    else
        v[i].push_back(e);
}
#endif // BUCKETSORT_H
