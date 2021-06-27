/* Run command: g++ -std=c++11 HeapDemo.cpp -I dsacpp/include -o heaptest
 * Then run ./heaptest <heap_size>
 * (replace <heap_size> with a number)
 */

#include <iostream>
#include "heap/Heap.h"
#include "util/ArrayLib.h"
#include <vector>
#include <map>

using namespace std;

template <typename T>
bool isValidHeap(T *elements, int size) {
    for (int i = 1; i < size; i++)
        if (elements[i] < elements[(i - 1) >> 1])
            return false;
    return true;
}

template <typename T>
T *copyFromHeap(Heap<T> &heap) {
    T *dest = new T[heap.size()];
    int ind = 0;
    for (auto it = heap.begin(); it != heap.end(); ++it)
        dest[ind++] = *it;
    return dest;
}

int main(int argc, char** argv) {
    int TEST_SIZE = stoi(argv[1]);
    Heap<int> minHeap;
    if (minHeap.size() != 0) {
        cout << "Fuck you idiot! Why did you change the lecturer's constructor?" << endl;
        return 0;
    }

    int *item = genIntArray(TEST_SIZE, 0, TEST_SIZE * 2);
    minHeap.heapify(item, TEST_SIZE);
    delete[] item;
    item = copyFromHeap(minHeap);

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
            int *temp = copyFromHeap(minHeap);
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
