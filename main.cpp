#include <iostream>
#include "heap/Heap.h"

using namespace std;

int comparator(int*& lhs, int*& rhs){
    if(*lhs < *rhs) return -1;
    else if(*lhs > *rhs) return +1;
    else return 0;
}

void heap_quiz(){
    int ptr[] = {50, 20, 70, 5, 15, 80};
    Heap<int*> heap(&comparator);
    for(int idx=0; idx< 6; idx++) heap.push(&ptr[idx]);
    heap.println();
}

int main() {
    heap_quiz();
}