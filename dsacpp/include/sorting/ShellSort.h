/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShellSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 16:45
 */

#ifndef SHELLSORT_H
#define SHELLSORT_H
#include "sorting/ISort.h"

template<class T>
class ShellSort: public ISort<T>{
private:
    int *num_segment_list;
    int num_phases;
    
public:
    ShellSort(int *num_segment, int num_phases){
        this->num_phases = num_phases;
        this->num_segment_list = new int[num_phases];
        for(int idx=0; idx < num_phases; idx++) 
            this->num_segment_list[idx] = num_segment[idx];
    }
    ~ShellSort(){
        delete []num_segment_list;
    }
    
    
    void sortSegment(T array[], int size, 
            int segment_idx, int cur_segment_total,
            int (*comparator)(T&, T&)){
        //YOUR CODE HERE
    }
    /*
    shell_sort
    -----------
    num_segments: 
         + The first must be 1, for examples: [1,3,7]
    */
    void sort(T array[], int size, int (*comparator)(T&,T&), int stride = 1){
        //YOUR CODE HERE
        for (int segment_idx = num_phases - 1; segment_idx >= 0; --segment_idx) {
            int gap = num_segment_list[segment_idx];
            for (int i = gap * stride; i < size * stride; i += stride) {
                T temp = array[i]; int j;
                for (j = i; j >= gap * stride && (*comparator)(array[j - gap * stride], temp) > 0; j -= gap * stride)
                    array[j] = array[j - gap * stride];
                array[j] = temp;
            }
        }
    }
};

#endif /* SHELLSORT_H */

