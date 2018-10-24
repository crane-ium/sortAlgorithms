#ifndef SORT_CONTROLS_H
#define SORT_CONTROLS_H

#include <cstdlib>
#include <random>
#include <time.h>
#include <cassert>
#include <iomanip>

using namespace std;

static const bool DEBUG = true;

//Sorting array control functions
template<class T> //shuffles an array
T* shuffle(T *arr, const size_t& size){
    T* shuffled_arr = new T[size];
    for(int i = 0; i < size; i++)
        shuffled_arr[i] = arr[i];
    srand(time(NULL));
    for(size_t i = 0; i < 2*size; i++)
        swap(shuffled_arr[rand()%size], shuffled_arr[rand()%size]);
    return shuffled_arr;
}
template<class T>
void copy_array(T* &copy, const T orig[], const size_t& size){
    copy = new T[size];
    for(size_t i = 0; i < size; i++)
        copy[i] = orig[i];
}
template <class T>
bool verify_inc(const T a[], const size_t& size){
    assert(size >= 2);
    //check that the list is not-decreasing
    for(size_t i = 1; i < size; i++){
        if(a[i-1] > a[i])
            return false;
    }
    return true;
}
template <class T>
bool verify_dec(const T a[], const size_t& size){
    assert(size >= 2);
    //check that the list is not-increasing
    for(size_t i = 1; i < size; i++){
        if(a[i-1] < a[i])
            return false;
    }
    return true;
}
template<class T>
bool verify_inc_abs(const T a[], const size_t& size){
    assert(size >= 2);
    //check that the list is not-increasing
    for(size_t i = 1; i < size; i++){
        if(a[i-1] >= a[i])
            return false;
    }
    return true;
}
template<class T>
bool verify_dec_abs(const T a[], const size_t& size){
    assert(size >= 2);
    //check that the list is not-increasing
    for(size_t i = 1; i < size; i++){
        if(a[i-1] <= a[i])
            return false;
    }
    return true;
}
//return a string "SORTED" or "NOT SORTED" depending if a[] is sorted
template <class T>
string verifystr(const T a[], unsigned int  size);

//print the array if status_only is true along with info on sortedness of a[]
template <class T>
void print_array(const T a[], int size, bool status_only = false);

//print a[] from start to end
template <class T>
void print_array_segment(const T a[], const size_t& start, const size_t& end, int interval=1){
    for(size_t i = start; i < end; i+=interval)
        cout << "[" << setw(4) << setfill('0') << i << "]: " << a[i] << endl;
}

//Definitions


#endif // SORT_CONTROLS_H
