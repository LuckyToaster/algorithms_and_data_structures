#include "sorting.hpp"

//#define beep template
//#define bop <typename T>

#include <iostream>
#include <type_traits>
#include <chrono>
#include <string>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ostream;


beep bop void test_sorting_algo(void (* func)(T*, size_t), T* arr, size_t size, T* expected, string name) {
    func(arr, size);

    for (size_t i = 0; i < size; i++) 
        if (arr[i] != expected[i]) {
            cerr << name << " => FAILED TEST" << endl;
            cout << "\tExpected: ";
            printarr(expected, size);
            cout << "\tbut got: ";
            printarr(arr, size);
            return;
        }
    cout << name << " => PASSED TEST" << endl;
}


beep bop void benchmark(void (* func)(T*, size_t), T* arr, size_t arr_s, string name) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now(); 
    func(arr, arr_s);
    auto end = high_resolution_clock::now(); 
    auto nanos = duration_cast<nanoseconds>(end - start).count();
    cout << name << " took " << nanos << " ns on a direct access array of size: " << arr_s << endl;
}


beep bop void printarr(T* arr, size_t s) {
    for (size_t i = 0; i < s; i++) {
        if (i == 0) cout << "[" << arr[i] << ", ";
        else if (i == s - 1) cout << arr[i] << "]";
        else cout << arr[i] << ", ";
    }
    cout << endl;
}


beep bop void inssort(T* arr, size_t s) {
    for (size_t i = 1; i < s; i++) {
        auto val = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > val) {
            arr[j + 1] = arr[j];
            j -= 1;
        } 
        arr[j + 1] = val;
    }
}


beep bop void inssort_decreasing(T* arr, size_t s) {
    for (size_t i = 1; i < s; i++) {
        auto val = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < val) { // we just change arr[j] > val '<' 
            arr[j + 1] = arr[j];
            j -= 1;
        } 
        arr[j + 1] = val;
    }
}


beep bop static void merge(T* arr, size_t left, size_t middle, size_t right) {
    const size_t S1 = middle - left + 1;
    const size_t S2 = right - middle;

    T arr1[S1];
    T arr2[S2];

    for (size_t i = 0; i < S1; i++) arr1[i] = arr[i + left]; 
    for (size_t i = 0; i < S2; i++) arr2[i] = arr[i + middle + 1]; 

    if (S1 > 0 && S2 > 0) {
        for (size_t idx_1 = 0, idx_2 = 0, i = left; i <= right; i++) { // since right is an index, should <= instead of <
            if ((idx_1 < S1 && idx_2 >= S2) || arr1[idx_1] <= arr2[idx_2]) { // first part of || copied from yt
                arr[i] = arr1[idx_1];
                idx_1++;
            } else {
                arr[i] = arr2[idx_2];
                idx_2++;
            }
        }
    }
}


beep bop static void mergesort(T* arr, size_t left, size_t right) {
    if (left < right) {
        size_t middle = (left + right) / 2;
        mergesort(arr, left, middle);
        mergesort(arr, middle + 1, right);  // should re-define the new right???? --- deffo yes
        merge(arr, left, middle, right); 
    }
}


beep bop void mergesort(T* arr, size_t size) {
    mergesort(arr, 0, size - 1);
}

