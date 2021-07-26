/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListTest.h
 * Author: LTSACH
 *
 * Created on 25 August 2020, 11:15
 */

#ifndef COMMONS_H
#define COMMONS_H
#include "doctest.h"
/*
//ASSIGMENT 1
#include "list/XArrayList.h"
#include "list/SLinkedList.h"
#include "list/DLinkedList.h"
#include "stacknqueue/IDeck.h"
#include "stacknqueue/Stack.h"
#include "stacknqueue/Queue.h"

//ASSIGMENT 2
#include "tree/AVL.h"
*/

//ASSIGMENT 3
/*
#include "heap/Heap.h"
#include "hash/XHashMap.h"
#include "sorting/StraightInsertionSort.h"
#include "sorting/ShellSort.h"
#include "sorting/StraightSelectionSort.h"
#include "sorting/BubbleSort.h"
#include "sorting/HeapSort.h"
#include "sorting/QuickSort.h"
#include "sorting/SLinkedListSE.h"
#include "sorting/DLinkedListSE.h"
*/


//ASSIGMENT 4
#include "graph/UGraphModel.h"
#include "graph/DGraphModel.h"
#include "graph/TopoSorter.h"
#include "list/DLinkedList.h"

//Common libs
#include "util/FileIOLib.h"
#include "util/ArrayLib.h"

//System libs
#include <sstream>
#include <bits/stdc++.h>
#include <cmath>
#define EPSILON (1e-7)
using namespace std;

/*
 REF: https://www.thecrazyprogrammer.com/2021/01/c-string-trim.html
 */
string trimstring(string str) {
    const char* typeOfWhitespaces = " \t\n\r\f\v";
    str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
    str.erase(0,str.find_first_not_of(typeOfWhitespaces));
    return str;
}

using namespace std;

int nsizes = 20;
int max_length = 100;


int min_comparator(int& a, int& b){
    if(a < b) return -1;
    else if(a > b) return +1;
    else return 0;
}
int max_comparator(int& a, int& b){
    if(a < b) return +1;
    else if(a > b) return -1;
    else return 0;
}

/*
 T: char, number, string
 */
template<class T>
bool comparator(T& lhs, T& rhs){
    return lhs==rhs;
}


string vertex2str(char& v){
    stringstream os;
    os << v;
    return os.str();
}
string vertex2str(int& v){
    stringstream os;
    os << v;
    return os.str();
}


int hash_code(char& key, int size){
    return (int)key %size;
}
int hash_code(int& key, int size){
    return key %size;
}
bool equal(float a, float b){
    return abs(a - b) < EPSILON;
}


char    A='A', B='B', C='C', D='D', E='E', \
        F='F', G='G', H='H', I='I', J='J', \
        K='K', L='L', M='M', N='N', O='O', \
        P='P', Q='Q', R='R', S='S', T='T', \
        U='U', V='V', X='X', Y='Y', Z='Z', W='W';

#endif /* COMMONS_H */

