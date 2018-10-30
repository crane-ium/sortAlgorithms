#include <windows.h>
#include <iostream>
#include <time.h>
#include <functional>
#include <sorts>
#include <vector>
#include "sort_controls.h"
#include "mergesort.h"
#include "random"

using namespace std;

template<typename T>
T* get_rand_array(const size_t& size, const size_t& min, const size_t& max);
template<typename T>
T* get_clustered_array(const size_t& size, const size_t& min, const size_t& max);
template<typename T, typename Func>
double time_f(T* &a, const size_t& s, Func f, bool output=false, ostream& outs=cout);
template<typename T>
T get_average(T* a, const size_t& s);
//void time_f(T* a, const size_t& s, void(*f)(T*, const size_t)); //wasn't working
template<typename T, typename Func>
double time_xf(const size_t& size, const size_t& runs, Func f, const size_t a_max);
template<class Func>
void print_int_sort(const size_t& size, const size_t& runs
                    , Func f, const string& s);
template<class T>
void print_int_sort2(const size_t& size, const size_t& runs
                    , void(*f)(T*&, const size_t), const string& s);
template<class Func>
void print_int_clustered_sort(const size_t& size, const size_t& runs
                    , Func f, const string& s);

int main()
{
    size_t size = 1000, runs = 5, size2 = 100000, size3 = 100000, size4=100000;
    srand(time(NULL));
////    //test mergesort
    print_int_sort(size2, runs, mergesort<int>, "mergesort");
////    //test bubblesort
    print_int_sort(size, runs, bubblesort<int>, "bubblesort");
////    //test insertionsort
    print_int_sort(size, runs, insertionsort<int>, "insertionsort");
////    //test quicksort
    print_int_sort(size2, runs, quicksort<int>, "quicksort");
////    //test heapsort
    print_int_sort(size2, runs, heapsort<int>, "heapsort");
////    //test heaporder: the function that turns an array into heap array
    print_int_sort(size2, runs, heaporder_simple<int>, "heaporder-simple");
////    //test bucketsort
    print_int_sort(size4, runs, bucketsort<int>, "bucketsort");
//    //test radixsort - myversion
    print_int_sort(size2, runs, radixsort<int>, "radixsort");
//    //test radixsort - optimized version
    print_int_sort(size2, runs, radixsort_two<int>, "radixsortv2.0");
    //test bucketsort - optimized
    print_int_sort(size2, runs, bucketsort_two<int>, "bucketsortv2.0");
    //countingsort
    print_int_sort(size2, runs, countingsort, "countingsort");
//    //CLUSTERED ARRAYS - NORMAL DISTRIBUTION
////    //test mergesort
//    print_int_clustered_sort(size2, runs, mergesort<int>, "mergesort");
////    //test bubblesort
//    print_int_clustered_sort(size, runs, bubblesort<int>, "bubblesort");
////    //test insertionsort
//    print_int_clustered_sort(size, runs, insertionsort<int>, "insertionsort");
////    //test quicksort
//    print_int_clustered_sort(size2, runs, quicksort<int>, "quicksort");
////    //test heapsort
//    print_int_clustered_sort(size2, runs, heapsort<int>, "heapsort");
////    //test heaporder: the function that turns an array into heap array
//    print_int_clustered_sort(size2, runs, heaporder_simple<int>, "heaporder-simple");
////    //test bucketsort
//    print_int_clustered_sort(size2, runs, bucketsort<int>, "bucketsort");
//    //test radixsort - myversion
//    print_int_clustered_sort(size2, runs, radixsort<int>, "radixsort");
//    //test radixsort - optimized version
//    print_int_clustered_sort(size2, runs, radixsort_two<int>, "radixsortv2.0");
////    size_t s = 5;

    return 0;
}

template<typename T>
T* get_rand_array(const size_t &size, const size_t& min, const size_t& max){
    assert(size>0);
    T* temp = new T[size];
    //Form a 32767 x 32767 matrix to generate a larger random int
    long long randint = rand() * 32767 + rand();
    for(size_t i = 0; i < size; i++){
        randint = rand() * 32767 + rand();
        temp[i] = randint % (max+min) + min;
    }
    return temp;
}
template<typename T>
T* get_clustered_array(const size_t& size, const size_t& min, const size_t& max){
    //returns an array with a normal distribution
    long long randint1 = rand() * 32767 + rand();
    long long randint2 = rand() * 32767 + rand();
    T* temp = new T[size];
    for(size_t i = 0; i < size; i++){
        randint1 = rand() * 32767 + rand();
        randint2 = rand() * 32767 + rand();
        temp[i] = (randint1%((max-(min+1)/2)/2)) + (randint2%((max-min/2+1)/2))+min;
    }
    return temp;
}

template<typename T, typename Func>
double time_f(T *&a, const size_t& s, Func f, bool output, ostream& outs){
    static timer clockboy; //implementation of data encapsulation for time
//    LARGE_INTEGER frequency, t_start, t_end;
//    double elapsed;
    if(output)
        outs << "Running function...\n";
//    QueryPerformanceFrequency(&frequency);
//    QueryPerformanceCounter(&t_start);
    clockboy.start();
    f(a, s); //run function
    clockboy.end();
//    QueryPerformanceCounter(&t_end);
//    elapsed = (t_end.QuadPart - t_start.QuadPart)
//                * 1000.0 / frequency.QuadPart;
//    if(output)
//        outs << "The function ran in " << setprecision(3)
//             << elapsed << " milliseconds" << endl;
    return clockboy();
}
template<typename T, typename Func>
double time_xf(const size_t &size, const size_t& runs, Func f, const size_t a_max){
    size_t a_s = size;;
//    double* t_arr = new double[runs];
    double time = 0;
    T* arr_n;

    arr_n = get_rand_array<int>(a_s, 0, a_max);
    for(size_t i = 0; i < runs; i++){
        shuffle(arr_n, size);
        time += time_f(arr_n, a_s, f, false);
    }
    delete[] arr_n;
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

template<class Func>
void print_int_sort(const size_t& size, const size_t& runs
                    , Func f, const string& s){
    double average1, average2, average3;
    average1 = time_xf<int>(size, runs, f, size/10);
    average2 = time_xf<int>(size, runs, f, size);
    average3 = time_xf<int>(size, runs, f, size*10);
    cout << setfill(' ');
    cout << "| " << left << setw(17) << s << " | Average time for " << setw(9)
         << size << " elements: " << endl << setiosflags(ios::fixed)
         << "1:10 elements:duplicates: "
         << setw(9) << setprecision(3) << right << average1 << " milliseconds\n"
         << "1:1  elements:duplicates: " << setw(9) << average2 << " milliseconds\n"
         << "10:1 elements:duplicates: " << setw(9) << average3 << " milliseconds\n";
    int* arr = get_rand_array<int>(size, 0, size);
    shuffle(arr, size);
    f(arr, size); //call the sort function
    //Let's print the first three and last three elements
    cout << s << " is " << verifystr(verify_inc<int>, arr, size) << endl;
    for(size_t i = 0; i < 3; i++)
        cout << "  [" << setfill('0') << setw(log10(size)) << i << "] : "
             << right << setfill(' ') << setw(log10(size)+1) << arr[i]  << endl;
    for(size_t i = size-3; i < size; i++)
        cout << "  [" << setfill('0') << setw(log10(size)) << i << "] : "
             << right << setfill(' ') << setw(log10(size)+1) << arr[i]  << endl;
    delete[] arr;
}
template<class T>
void print_int_sort2(const size_t& size, const size_t& runs
                     , void(*f)(T*&, const size_t), const string& s){
    double average;
    average = time_xf<int>(size, runs, f);
    cout << setfill(' ');
    cout << "| " << left << setw(17) << s << " | Average time for " << setw(9)
         << size << " elements: " << setiosflags(ios::fixed) << setw(9)
         << setprecision(3) << right << average << " milliseconds\n";
    int* arr = get_rand_array<int>(size, 0, size*10);
    shuffle(arr, size);
    f(arr, size); //call the sort function
    //Let's print the first three and last three elements
    cout << s << " is **********-*** " << verifystr(verify_inc<int>, arr, size) << endl;
    for(size_t i = 0; i < 3; i++)
        cout << "  [" << setfill('0') << setw(log10(size)) << i << "] : "
             << right << setfill(' ') << setw(log10(size)+1) << arr[i]  << endl;
    for(size_t i = size-3; i < size; i++)
        cout << "  [" << setfill('0') << setw(log10(size)) << i << "] : "
             << right << setfill(' ') << setw(log10(size)+1) << arr[i]  << endl;
    delete[] arr;
    cout<<"--------- END print int sort 2 ------------"<<endl;
}
template<class Func>
void print_int_clustered_sort(const size_t& size, const size_t& runs
                    , Func f, const string& s){
    double average;
    average = time_xf<int>(size, runs, f);
    cout << setfill(' ');
    cout << "| " << left << setw(17) << s << " | Average time for " << setw(9)
         << size << " elements: " << setiosflags(ios::fixed) << setw(9)
         << setprecision(3) << right << average << " milliseconds\n";
    int* arr = get_clustered_array<int>(size, 0, size*10);
    shuffle(arr, size);
    f(arr, size); //call the sort function
    //Let's print the first three and last three elements
    cout << s << " is " << verifystr(verify_inc<int>, arr, size) << endl;
    for(size_t i = 0; i < 3; i++)
        cout << "  [" << setfill('0') << setw(log10(size)) << i << "] : "
             << right << setfill(' ') << setw(log10(size)+1) << arr[i]  << endl;
    for(size_t i = size-3; i < size; i++)
        cout << "  [" << setfill('0') << setw(log10(size)) << i << "] : "
             << right << setfill(' ') << setw(log10(size)+1) << arr[i]  << endl;
    delete[] arr;
}
