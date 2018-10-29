#ifndef BUCKETSORT_TWO_H
#define BUCKETSORT_TWO_H

#include "sort_controls.h"
#include "insertionsort.h"

template<class T>
void bucketsort_two(T* &arr, const size_t size);
template<class T>
void b_get_max(T* arr, const size_t size);

template<class T>
/**
 * @brief bucketsort_two: Version 2.0 of bucketsort after knowledge gain
 *      after doing radixsort!
 * @param arr
 * @param size
 */
void bucketsort_two(T* &arr, const size_t size){
    //Let's put things in buckets based on their range
    static const size_t range = 200; //bucket range lookup
    T* temp = new T[size];
    T max = get_max(arr, size);
    size_t max_i = (size_t)(max/range);
    size_t count1[max_i + 2] = {0};
    size_t count2[max_i + 2] = {0};
    count1[max_i + 1] = size;
    count2[max_i + 1] = size;
    for(size_t i = 0; i < size; i++){
        size_t arr_e = arr[i]/range;
        count1[arr_e]++;
        count2[arr_e]++;
    }
    for(size_t i = 1; i < (size_t)(max/range)+1; i++){
        count1[i] += count1[i-1];
        count2[i] += count2[i-1];
    }
    for(size_t i = 0; i < size; i++){
        //put elements of arr into their corresponding bucket
        size_t index = arr[i]/range;
        temp[count1[index]-1] = arr[i];
        count1[index]--;
    }
    for(size_t i = 0; i < max_i+1; i++){ //apply insertion to each bucket
        insertionsort((temp+count1[i]), count1[i+1]-count1[i]);
    }
    delete[] arr;
    arr = temp;
    //verify
//    assert(verify_inc(arr, size));
}
template<class T>
void b_get_max(T* arr, const size_t size){
    T max = 0;
    for(size_t i = 0; i < size; i++)
        if(arr[i] > max)
            max = arr[i];
    return max;
}
#endif // BUCKETSORT_TWO_H
