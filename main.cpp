#include <windows.h>
#include <iostream>
#include <time.h>
#include <functional>
#include <sorts>
#include "sort_controls.h"
#include "mergesort.h"
#include "random"


using namespace std;

template<typename T>
T* get_rand_array(const size_t& size, const size_t& min, const size_t& max);
template<typename T, typename Func>
double time_f(T* a, const size_t& s, Func f, bool output=false, ostream& outs=cout);
template<typename T>
T get_average(T* a, const size_t& s);
//void time_f(T* a, const size_t& s, void(*f)(T*, const size_t)); //wasn't working
template<typename T, typename Func>
double time_xf(const size_t& size, const size_t& runs, Func f);

int main()
{
    double average;
    size_t size = 1000, runs = 100, size2 = 10000, size3 = 100000;
    srand(time(NULL));
//    //test mergesort
//    average = time_xf<int>(size2, runs, mergesort<int>);
//    cout << "Average mergesort for " << size2 << " elements: "
//         << average << " milliseconds\n";
//    //test insertionsort
//    average = time_xf<int>(size, runs, bubblesort<int>);
//    cout << "Average bubblesort " << size << " elements: "
//         << average << " milliseconds\n";
//    //test insertionsort
//    average = time_xf<int>(size, runs, insertionsort<int>);
//    cout << "Average insertionsort " << size << " elements: "
//         << average << " milliseconds\n";
//    //test quicksort
//    average = time_xf<int>(size2, runs, quicksort<int>);
//    cout << "Average quicksort " << size2<< " elements: "
//         << average << " milliseconds\n";
    //test heapsort
    average = time_xf<int>(size, runs, heapsort<int>);
    cout << "Average heapsort " << size << " elements: "
         << average << " milliseconds\n";


//    print_array(arr,10);
//    insertionsort(arr, 10);
//    print_array(arr,10);

    return 0;
}

template<typename T>
T* get_rand_array(const size_t &size, const size_t& min, const size_t& max){
    assert(size>0);
    srand(time(NULL));
    T* temp = new T[size];
    for(size_t i = 0; i < size; i++){
        temp[i] = rand() % (max+min) + min;
    }
    return temp;
}

template<typename T, typename Func>
double time_f(T *a, const size_t& s, Func f, bool output, ostream& outs){
    LARGE_INTEGER frequency, t_start, t_end;
    double elapsed;
    if(output)
        outs << "Running function...\n";
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&t_start);
    f(a, s); //run function
    QueryPerformanceCounter(&t_end);
    elapsed = (t_end.QuadPart - t_start.QuadPart)
                * 1000.0 / frequency.QuadPart;
    if(output)
        outs << "The function ran in " << setprecision(3)
             << elapsed << " milliseconds" << endl;
    return elapsed;
}
template<typename T, typename Func>
double time_xf(const size_t &size, const size_t& runs, Func f){
    size_t a_s = size;
//    double* t_arr = new double[runs];
    double time = 0;
    T* arr_n;

    arr_n = get_rand_array<int>(a_s, 0, a_s*10);
    for(size_t i = 0; i < runs; i++){
        shuffle(arr_n, size);
        time += time_f(arr_n, a_s, f, false);
    }
    return time/runs;
}
template<typename T>
T get_average(T* a, const size_t& s){
    T avg = T();
    for(size_t i = 0; i < s; i++){
        avg += a[i];
    }
    avg /= s;
    return avg;
}
