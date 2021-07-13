#include <iostream>
using namespace std;

#include "list/DLinkedList.h"

DLinkedList<int> test() {
    DLinkedList<int> ret;
    for (int i = 0; i < 10; ++i) ret.add(i);
    return ret;
}

int main() {
    DLinkedList<int> sth = test();
    sth.println();
}