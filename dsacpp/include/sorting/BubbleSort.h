/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BubbleSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 17:16
 */

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "sorting/ISort.h"

template<class T>
class BubbleSort: public ISort<T>{
public:
    void sort(T array[], int size, int (*comparator)(T&,T&), int stride = 1){
        //YOUR CODE HERE
        for (int floor = size - 1; floor > 0; --floor) {
            bool sorted = true;
            for (int i = 0; i < floor * stride; i += stride)
                if ((*comparator)(array[i], array[i + stride]) == 1) {
                    T temp = array[i];
                    array[i] = array[i + stride];
                    array[i + stride] = temp;
                    sorted = false;
                }
            if (sorted) break;
        }
    }
};


#endif /* BUBBLESORT_H */

