//radixsort -*- C++ -*-

//Copyright (C) 2018-2018 Stephen Crane and Co

//This file is part of the sorting algorithm library.
//I hereby grant any one who loves my code to use, redistribute, and/or
//modify my code for personal or commercial use under the
//Stephen Is Best General LIcense as published by Stephen Crane.

//No guarantees though.

/** @file include/radixsort
 * Standard C++ header
 */
#ifndef RADIXSORT_H
#define RADIXSORT_H

#include "sort_controls.h"
#include <vector>
template<class T>
void radixsort(T* arr, const size_t& size);
template<class T>
void empty_buckets(vector<vector<T> >& v, T* arr, size_t& i);
template<class T>
void move_buckets(vector<vector<T> >& sender, vector<vector<T> >& reciever
                  , vector<vector<T> >& b3, const size_t& digit);

template<class T> //Though this is templated, we only accept numbers atm
void radixsort(T* arr, const size_t& size){
    //we will use 30 buckets
    vector<vector<T> > buckets1, buckets2, buckets3;
    for(size_t i = 0; i < 10; i++){
        buckets1.push_back(vector<T>());
        buckets2.push_back(vector<T>());
        buckets3.push_back(vector<T>());
    }
    //We need to track digit we are tracking, starting from right
    size_t digit = 0, index=0;
    bool b_flag = true;
    //put everything into buckets first, and the first setup of buckets is different
    //We are assuming EVERYTHING IS 0 TO POSITIVE INFINITY
    for(size_t i = 0; i < size; i++){
        if(arr[i] < 10){
            buckets3[arr[i]].push_back(arr[i]);
        }else{
            buckets1[arr[i]%10].push_back(arr[i]);
        }
    }
    //We will need two nested loops, the outer one will loop k times
    // and the inner loops roughly times
    size_t count;
    while(index < size){
        count=0;
        //empty buckets3, the bucket that contains integers with leftmost being current max digit
        empty_buckets(buckets3, arr, index);

        digit++;
        b_flag ^= true;
//        cout << "Going to move " << digit << endl;
        //now reorganize your buckets
        //Move from bucket(digit%2) to bucket((digit+1)%2)
        //Order now matters! That's why we move bucket 0 first
        for(size_t i = index; i < size; i++){
            if(b_flag){ //digit%2 == 0
                move_buckets(buckets2, buckets1, buckets3, digit);
            }else{
                move_buckets(buckets1, buckets2, buckets3, digit);
            }
        }
    }
}
template<class T>
void empty_buckets(vector<vector<T> >& v, T* arr, size_t& i){
    size_t count=0; //go through all 10 buckets and move them into array
    size_t index;
    while(count<10){
        while(count < 10 && !v[count].size())
            count++;
        if(count>=10)
            return;
        index=0;
        while(index < v[count].size()){ //move buckets into array sorted!
            arr[i] = v[count][index];
            index++;
            i++;
        }
        v[count].clear();
    }
}

template<class T>
void move_buckets(vector<vector<T> >& sender, vector<vector<T> >& reciever
                  , vector<vector<T> > &b3, const size_t& digit){
    //move items from sender to reciever/bucket3 based on digit
    size_t count=0;
    size_t index;
    static size_t d_val; //digit value
    while(count<10){
        while(count < 10 && !sender[count].size()) // == 0
            count++;
        if(count >= 10)
            return;
        index=0;
        while(index < sender[count].size()){
            T temp = sender[count][index];
            T power = pow(10,digit);
            if(temp < 10*power){ //move them to bucket3 to place in array
                d_val = temp/power%10;
                b3[d_val].push_back(temp);
            }else{ //hop them over to the alternate bucket
                d_val = temp/power%10;
                reciever[d_val].push_back(temp);
            }
            index++;
        }
        sender[count].clear();
    }
}
#endif // RADIXSORT_H
