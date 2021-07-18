/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StraightInsertionSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 16:24
 */

#ifndef STRAIGHTINSERTIONSORT_H
#define STRAIGHTINSERTIONSORT_H
#include "sorting/ISort.h"

template<class T>
class StraightInsertionSort: public ISort<T>{
public:
    void sort(T array[], int size, int (*comparator)(T&,T&), int stride = 1){
        //YOUR CODE HERE
        for (int i = stride; i < size * stride; i += stride) {
            T temp = array[i];
            int j;
            for (j = i; j > 0 && (*comparator)(temp, array[j - stride]) < 0; j -= stride)
                array[j] = array[j - stride];
            array[j] = temp;
        }
    }
};

#endif /* STRAIGHTINSERTIONSORT_H */

