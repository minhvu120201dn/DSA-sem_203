/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HeapSort.h
 * Author: LTSACH
 *
 * Created on 14 September 2020, 18:10
 */

#ifndef HEAPSORT_H
#define HEAPSORT_H
#include "sorting/ISort.h"
#include "heap/Heap.h"

template<class T>
class HeapSort: private Heap<T>, public ISort<T>{
public:
    HeapSort(   int (*comparator)(T& , T&)=0, 
                void (*deleteUserData)(Heap<T>*)=0 ):
                Heap<T>(comparator, deleteUserData){
    }
    void sort(T array[], int size, int (*comparator)(T&,T&)=0, int stride = 1){  
        //YOUR CODE HERE
        this->comparator = comparator;
        //this->heapify(array, size);
        for (int i = 0; i < size * stride; i += stride)
            this->push(array[i]);
        int ind = 0;
        while (!this->empty())
            array[ind] = this->pop(), ind += stride;
    }         
                
};


#endif /* HEAPSORT_H */

