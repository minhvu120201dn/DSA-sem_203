#include <iostream>
#include "sorting/QuickSort.h"

using namespace std;

template <typename T>
int pickupZero(T*, int) { return 0; }

int main() {
    QuickSort<int> sorter;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    sorter.sort(arr, 9, SortSimpleOrder<int>::compare4Ascending);
    for (int x : arr) cout << x << ' ';
}