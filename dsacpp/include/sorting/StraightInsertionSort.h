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
    void sort(T array[], int size, int (*comparator)(T&,T&)){
        //YOUR CODE HERE
        for (int i = 1; i < size; ++i) {
            T temp = array[i];
            int j;
            for (j = i; j > 0 && (*comparator)(temp, array[j - 1]) < 0; --j)
                array[j] = array[j - 1];
            array[j] = temp;
        }
    }
};

#endif /* STRAIGHTINSERTIONSORT_H */

