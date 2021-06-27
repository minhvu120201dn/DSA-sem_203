#include <iostream>
#include "heap/Heap.h"
#include "util/ArrayLib.h"
#include <vector>
#include <map>

using namespace std;

#define DEMO

#ifndef DEMO

#define TEST_SIZE 5000

template <typename T>
bool isValidHeap(T *elements, int size) {
    for (int i = 1; i < size; i++)
        if (elements[i] < elements[(i - 1) >> 1])
            return false;
    return true;
}

int main() {
    Heap<int> minHeap;
    if (minHeap.size() != 0) {
        cout << "Fuck you idiot! Why did you change the lecturer's constructor?" << endl;
        return 0;
    }

    int *item = genIntArray(TEST_SIZE, 0, TEST_SIZE * 2);
    minHeap.heapify(item, TEST_SIZE);
    {
        int ind = 0;
        for (auto it = minHeap.begin(); it != minHeap.end(); ++it)
            item[ind++] = *it;
    }
    cout << "Heap before testing:\n";
    minHeap.println();

    if (minHeap.size() != TEST_SIZE || !isValidHeap(item,TEST_SIZE)) {
        cout << "Heapify function is wrong" << endl;
        return 0;
    }

    map<int,int> available;
    for (auto it = minHeap.begin(); it != minHeap.end(); ++it)
        ++available[*it];

    int size = TEST_SIZE;
    vector<int> removed;
    for (int i = 0; i < TEST_SIZE; i++) {
        int e = rand() % TEST_SIZE;
        removed.push_back(item[e]);
        minHeap.remove(item[e]);
        if (available[item[e]] == 0) {
            if (minHeap.size() != size) {
                cout << "Removed elements:\n";
                for (auto x : removed) cout << x << ',';
                cout << endl;
                cout << "Heap after testing:\n";
                minHeap.println();
                cout << "You should not have removed the last element!" << endl;
                return 0;
            }
        }
        else {
            --available[item[e]];
            if (minHeap.size() != --size) {
                cout << "Removed elements:\n";
                for (auto x : removed) cout << x << ',';
                cout << endl;
                cout << "Heap after testing:\n";
                minHeap.println();
                cout << "You should have removed the last element!" << endl;
                return 0;
            }
            if (!isValidHeap(item,TEST_SIZE)) {
                cout << "Removed elements:\n";
                for (auto x : removed) cout << x << ',';
                cout << endl;
                cout << "Heap after testing:\n";
                minHeap.println();
                cout << "The heap is invalid!" << endl;
                return 0;
            }
        }
    }
}
#endif

#ifdef DEMO
int main() {
    int item[] = {1,6,2,13,8,8,14,17,17,12};
    Heap<int> minHeap;
    minHeap.heapify(item,sizeof(item)/sizeof(item[0]));
    minHeap.println();

    int removal[] = {17};
    for (int i = 0; i < sizeof(removal)/sizeof(removal[0]); i++) {
        minHeap.remove(removal[i]);
        minHeap.println();
        cout << minHeap.size() << endl;
    }
}
#endif