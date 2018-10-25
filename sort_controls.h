#ifndef SORT_CONTROLS_H
#define SORT_CONTROLS_H

#include <cstdlib>
#include <random>
#include <time.h>
#include <cassert>
#include <iomanip>
#include <functional>

using namespace std;

static const bool DEBUG = true;
//SIGNATURES
template<class T> //shuffles an array
void shuffle(T *arr, const size_t& size);
template<class T>
void copy_array(T* &copy, const T orig[], const size_t& size);
template <class T>
bool verify_inc(T* a, const size_t& size);
template <class T>
bool verify_dec(const T * a, const size_t& size);
template<class T>
bool verify_inc_abs(const T * a, const size_t& size);
template<class T>
bool verify_dec_abs(const T * a, const size_t& size);
template <class T, class Func>
string verifystr(Func f, T* a, const size_t& size);
template<class T>
bool verify(T* a, const size_t& size, bool asc=true, bool ab=false);
template <class T>
void print_array(const T * a, int size, bool status_only = false);

//print * a from start to end
template <class T>
void print_array_segment(const T * a, const size_t& start, const size_t& end, int interval=1);


//Sorting array control functions
template<class T> //shuffles an array
void shuffle(T *arr, const size_t& size){
    T* shuffled_arr = new T[size];
    for(size_t i = 0; i < size; i++)
        shuffled_arr[i] = arr[i];
    srand(time(NULL));
    for(size_t i = 0; i < 2*size; i++){
        swap(shuffled_arr[rand()%size], shuffled_arr[rand()%size]);
    }
    arr = shuffled_arr;
}
template<class T>
void copy_array(T* &copy, const T orig[], const size_t& size){
    copy = new T[size];
    for(size_t i = 0; i < size; i++)
        copy[i] = orig[i];
}
template <class T>
bool verify_inc(T* a, const size_t& size){
    assert(size >= 2);
    //check that the list is not-decreasing
    for(size_t i = 1; i < size; i++){
        if(a[i-1] > a[i])
            return false;
    }
    return true;
}
template <class T>
bool verify_dec(const T * a, const size_t& size){
    assert(size >= 2);
    //check that the list is not-increasing
    for(size_t i = 1; i < size; i++){
        if(a[i-1] < a[i])
            return false;
    }
    return true;
}
template<class T>
bool verify_inc_abs(const T * a, const size_t& size){
    assert(size >= 2);
    //check that the list is not-increasing
    for(size_t i = 1; i < size; i++){
        if(a[i-1] >= a[i])
            return false;
    }
    return true;
}
template<class T>
bool verify_dec_abs(const T * a, const size_t& size){
    assert(size >= 2);
    //check that the list is not-increasing
    for(size_t i = 1; i < size; i++){
        if(a[i-1] <= a[i])
            return false;
    }
    return true;
}
//return a string "SORTED" or "NOT SORTED" depending if * a is sorted
template <class T, class Func>
string verifystr(Func f, T* a, const size_t& size){
    if(f(a, size)) //?????????
        return "SORTED";
    else
        return "NOT SORTED";
}
template<class T>
bool verify(T* a, const size_t& size, bool asc, bool ab){
    if(asc){
        if(!ab)
            return verify_inc(a, size);
        else return verify_inc_abs(a, size);
    }else
        if(!ab)
            return verify_dec(a, size);
        else return verify_dec_abs(a, size);
}
template<class T>
T order_asc(T arr[], size_t& l, size_t& r);


//print the array if status_only is true along with info on sortedness of * a
template <class T>
void print_array(const T * a, int size, bool status_only){
    print_array_segment(a, 0, size);
    //print status
}

//print * a from start to end
template <class T>
void print_array_segment(const T * a, const size_t& start, const size_t& end, int interval){
    for(size_t i = start; i < end; i+=interval)
        cout << "[" << setw(4) << setfill('0') << i << "]: " << a[i] << endl;
}
template<class T>
T order_asc(T arr[], size_t& l, size_t& r){
    if(arr[l] <= arr[r]){
        l++;
        return arr[l-1];
    }else{//then arr[r] < arr[l]
        r++;
        return arr[r-1];
    }
}

template<class T>
struct sort_order{
    /**
     * @brief sort_order
     * @param ord: true/false : ascending/descending order
     * @param ab: true/false : NOT USEFUL HERE!absolute/not-absolute
     */
    sort_order(bool ord=true, bool ab=false): __order(ord),__order_abs(ab){}

    T operator()(T arr[], size_t& l, size_t& r){
        if(__order){
            if(arr[l] <= arr[r]){
                l++;
                return arr[l-1];
            }else{
                r++;
                return arr[r-1];
            }
        }else{
            if(arr[l] >= arr[r]){
                l++;
                return arr[l-1];
            }else{
                r++;
                return arr[r-1];
            }
        }
    }
private:
    bool __order, __order_abs;
};

//Definitions


#endif // SORT_CONTROLS_H
