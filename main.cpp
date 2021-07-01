#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting {
private:
    static void printArray(T* start, T* end)
    {
        int  size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << " ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T* start, T* middle, T* end) {
        // TODO
        T copy[end - start];
        for (int i = 0; i < end - start; ++i) copy[i] = start[i];
        int div1 = 0, div2 = middle - start; T *p = start;
        
        while (div1 < middle - start && div2 < end - start) {
            if (copy[div1] < copy[div2])
                *(p++) = copy[div1++];
            else
                *(p++) = copy[div2++];
        }
        if (div1 == middle - start)
            while (div2 < end - start)
                *(p++) = copy[div2++];
        else
            while (div1 < middle - start)
                *(p++) = copy[div1++];
    }

public:
    static void InsertionSort(T* start, T* end) {
        // TODO
        for (T *p = start + 1; p < end; ++p) {
            T temp = *p, *q;
            for (q = p; q > start && q[-1] > temp; --q)
                *q = q[-1];
            *q = temp;
        }
    }

    static void TimSort(T* start, T* end, int min_size) {
        // TODO
        // You must print out the array after using insertion sort and everytime calling method merge.
        for (T *s = start, *e = start + min_size; s < end; s = e, e += min_size) {
            if (e > end) e = end;
            InsertionSort(s, e);
        }
        cout << "Insertion sort: "; printArray(start, end);
        
        int m_times = 1;
        while (min_size < end - start) {
            T *s = start, *m = start + min_size, *e = m + min_size;
            while (s < end) {
                if (m > end) m = end;
                if (e > end) e = end;
                merge(s, m, e);
                cout << "Merge " << m_times++ << ": "; printArray(start, end);
                s = e, m = e + min_size, e = m + min_size;
            }
            min_size = min_size << 1;
        }
    }
};

int main() {
    int array[] = { 19, 20, 18, 17 ,12, 13, 14, 15, 1, 2, 9, 6, 4, 7, 11, 16, 10, 8, 5, 3 };
    int min_size = 4;
    Sorting<int>::TimSort(&array[0], &array[20], min_size);
}

/*
Insertion Sort: 17 18 19 20 12 13 14 15 1 2 6 9 4 7 11 16 3 5 8 10
Merge 1: 12 13 14 15 17 18 19 20 1 2 6 9 4 7 11 16 3 5 8 10
Merge 2: 12 13 14 15 17 18 19 20 1 2 4 6 7 9 11 16 3 5 8 10
Merge 3: 12 13 14 15 17 18 19 20 1 2 4 6 7 9 11 16 3 5 8 10
Merge 4: 1 2 4 6 7 9 11 12 13 14 15 16 17 18 19 20 3 5 8 10
Merge 5: 1 2 4 6 7 9 11 12 13 14 15 16 17 18 19 20 3 5 8 10
Merge 6: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
*/