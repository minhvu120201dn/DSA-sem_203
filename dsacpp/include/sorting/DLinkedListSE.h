/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    void sort(int (*comparator)(T&,T&)=0){
        //YOUR CODE HERE
        if (this->count == 0) return;

        this->tail->prev->next = NULL;
        if (!comparator) comparator = &SortSimpleOrder<T>::compare4Ascending;
        mergeSort(this->head->next, comparator);

        typename DLinkedList<T>::Node *p;
        for (p = this->head; p->next; p = p->next)
            p->next->prev = p;
        p->next = this->tail;
        this->tail->prev = p;
    };
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
    void mergeSort(typename DLinkedList<T>::Node*& head, int (*comparator)(T&,T&)=0){
        //YOUR CODE HERE
        if((head != 0) && (head->next != 0)){
            typename DLinkedList<T>::Node* second;
            devide(head, second);
            mergeSort(head, comparator);
            mergeSort(second, comparator);
            merge(head, second, comparator);
        }
    };
    void devide(typename DLinkedList<T>::Node*& first, typename DLinkedList<T>::Node*& second){
        //YOUR CODE HERE
        int count = 0;
        for (typename DLinkedList<T>::Node *p = first; p; p = p->next) ++count;
        count = count >> 1;
    
        second = first;
        for (int i = 1; i < count; ++i) second = second->next;
        typename DLinkedList<T>::Node *temp = second;
        second = second->next;
        temp->next = NULL;
    }
    void merge(typename DLinkedList<T>::Node*& first, typename DLinkedList<T>::Node*& second, int (*comparator)(T&,T&)=0){
        //YOUR CODE HERE
        if (!first || !second) {
            if (!first) first = second;
            return;
        }

        typename DLinkedList<T>::Node *head, *tail;
        if ((*comparator)(first->data, second->data) < 0) head = first, first = first->next;
        else head = second, second = second->next;
        tail = head;

        while (first && second)
            if ((*comparator)(first->data, second->data) < 0) tail->next = first, tail = tail->next, first = first->next;
            else tail->next = second, tail = tail->next, second = second->next;
        if (!first) tail->next = second;
        else tail->next = first;

        first = head;
    }
};

#endif /* DLINKEDLISTSE_H */

