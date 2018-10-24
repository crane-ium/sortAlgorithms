#include <iostream>
#include "sort_controls.h"

using namespace std;

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    int* arr_n;
    copy_array(arr_n, arr, 3);

    cout << verify_inc(arr, 3);
    arr_n = shuffle(arr, 10);
    print_array_segment(arr_n, 0, 10);

    return 0;
}
