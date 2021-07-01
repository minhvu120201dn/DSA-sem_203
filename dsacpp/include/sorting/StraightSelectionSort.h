/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StraightSelectionSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 17:10
 */

#ifndef STRAIGHTSELECTIONSORT_H
#define STRAIGHTSELECTIONSORT_H

#include "sorting/ISort.h"


template<class T>
class StraightSelectionSort: public ISort<T>{
public:   
    void sort(T array[], int size, int (*comparator)(T&,T&)){
        //YOUR CODE HERE
        for (int i = 0; i < size - 1; ++i) {
            int ind = i; T m = array[i];
            for (int j = i + 1; j < size; ++j)
                if ((*comparator)(array[j], m) < 0) ind = j, m = array[j];
            T temp = array[i];
            array[i] = array[ind];
            array[ind] = temp;
        }
    }
};



#endif /* STRAIGHTSELECTIONSORT_H */

