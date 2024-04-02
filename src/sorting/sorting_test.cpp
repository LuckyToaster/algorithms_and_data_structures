#include "sorting.hpp"

using std::string;

int main() {
    int arr[] = {5,3,1,4,2,8,9,7,6,0};
    int arr_sorted[] = {0,1,2,3,4,5,6,7,8,9};
    int arr_decreasing[] = {9,8,7,6,5,4,3,2,1,0};

    test_sorting_algo<int>(inssort, arr, 10, arr_sorted, string("Insertion Sort"));
    test_sorting_algo<int>(inssort_decreasing, arr, 10, arr_decreasing, string("Insertion Sort Decreasing"));

    int mergearr[] = {5,3,1,4,2,8,9,7,6,0};
    test_sorting_algo<int>(mergesort<int>, mergearr, 10, arr_sorted, string("Merge Sort"));

    return 0;
}