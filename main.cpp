#include <iostream>
#include "sort_controls.h"
#include "mergesort.h"

using namespace std;

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr2[5] = {1, 2, 3, 4, 5};

    int* arr_n;
    arr_n = shuffle(arr2, 5);

//    print_array_segment(arr_n, 0, 10);

//    cout << verifystr(verify_inc, arr_n, 10);

    //testing std::function
//    test_stdfunction([&arr_n](function<bool(int[], int)> foo){
//        cout << "I WANNA TEST THIS!\n";
//        int a[5] = {1, 2, 3, 4, 5};
//        foo(a, 5);
//    });

//    int* a = new int[3];
//    a[0] = 1;
//    a[1] = 2;
//    a[2] = 3;

//    test(a);

    print_array(arr_n, 5);

    mergesort(arr_n, 5);
    cout << endl;

    print_array(arr_n, 5);

    return 0;
}
