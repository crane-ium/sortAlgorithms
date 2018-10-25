#include <windows.h>
#include <iostream>
#include <time.h>
#include <functional>
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

int main()
{
    int* arr_n;
    size_t a_s = 100000;
    double* t_arr = new double[100];

    for(size_t i = 0; i < 100; i++){
        arr_n = get_rand_array<int>(a_s, 0, a_s*10);
        time_f(arr_n, a_s, shuffle<int>);
        t_arr[i] = time_f(arr_n, a_s, mergesort<int>);
    }
//    print_array(t_arr, 100);
    cout << "Average for mergesort: " << get_average(t_arr, 100) << " milliseconds\n";

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
template<typename T>
T get_average(T* a, const size_t& s){
    T avg = T();
    for(size_t i = 0; i < s; i++){
        avg += a[i];
    }
    avg /= s;
    return avg;
}
