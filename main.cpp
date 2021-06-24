#include <iostream>
#include "geom/Point3D.h"
#include "tree/AVL.h"
#include "stacknqueue/Queue.h"

using namespace std;

int main() {
    int ptr[] = {80, 10, 70, 15, 65, 20, 60, 40};
    AVL<int, int*> tree;
    for(int key: ptr) tree.add(key);
    cout << tree.height() << endl;
}