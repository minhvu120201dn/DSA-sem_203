#include <iostream>
#include "heap/Heap.h"

using namespace std;

int cmp(int& a, int& b) {
    if (a < b) return 1;
    else if (a == b) return 0;
    else return -1;
}

int main() {
    Heap<int> maxHeap(&cmp);

    int item[] = {6, 10, 7, 23, 15, 20, 8, 50};
    maxHeap.heapify(item,8);
    maxHeap.println();

    maxHeap.remove(15);
    maxHeap.println();
}