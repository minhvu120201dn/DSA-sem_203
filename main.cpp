#include <iostream>

#include "sorting/StraightInsertionSort.h"
#include "sorting/ShellSort.h"
#include "sorting/StraightSelectionSort.h"
#include "sorting/BubbleSort.h"
#include "sorting/HeapSort.h"
#include "sorting/QuickSort.h"
#include "util/Point.h"
#include "util/ArrayLib.h"

using namespace std;

/*
#define TEST_SIZE 10

int main() {
    int *item = genIntArray(10, 0, 1000);
    for (int i = 0; i < TEST_SIZE; ++i) cout << item[i] << ' ';
    cout << endl;

    HeapSort<int> heapsort;
    heapsort.sort(item, TEST_SIZE, &SortSimpleOrder<int>::compare4Ascending);
    for (int i = 0; i < TEST_SIZE; ++i) cout << item[i] << ' ';
    cout << endl;
}
*/

int main() {
    int item[] = {237, 539, 762, 542, 200, 753, 799, 129, 50, 337};
    for (int x : item) cout << x << ", ";
    cout << endl;

    HeapSort<int> heapsort;
    heapsort.sort(item, sizeof(item) / sizeof(item[0]), &SortSimpleOrder<int>::compare4Ascending);
    for (int x : item) cout << x << ", ";
    cout << endl;
}