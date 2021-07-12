#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

#include "list/XArrayList.h"
#include "list/SLinkedList.h"
#include "list/DLinkedList.h"
#include "list/IList.h"
#include "tree/BST.h"
#include "tree/AVL.h"
#include "tree/IBST.h"
#include "util/ArrayLib.h"
#include "geom/Vector3D.h"
#include <algorithm>
#include <climits>
#include <float.h>

inline int randInt() {
    return (rand() & 1) ? 1 : -1;
}

void add_test(string filename, int nsizes, int nexec, int ntries, int max_length) {
    std::default_random_engine engine = std::default_random_engine(static_cast<long unsigned int>(time(0)));
    ofstream fout;

    ///////////////////////////////////////////////////////
    ///////////////// Adding int items ////////////////////
    ///////////////////////////////////////////////////////
    fout.open("int_" + filename);
    fout << "size, XArrayList(ms), SLinkedList(ms), DLinkedList(ms), BST(ms), AVL(ms)" << endl;
    cout << "Adding int items" << endl;
    for (int test = 0; test < nexec; ++test) {
        XArrayList<int> arr;
        SLinkedList<int> sll;
        DLinkedList<int> dll;
        BST<int, int*> bst;
        AVL<int, int*> avl;
        int *sizes = genIntArray(nsizes, 0, max_length);
        sort(sizes, sizes + nsizes);
        for (int row = 0; row < nsizes; ++row) {
            int size = sizes[row];
            fout << size << ", ";
            uniform_int_distribution<int> kdist(0, size);
            int *items = genIntArray(ntries, INT_MIN, INT_MAX);
            { // XArrayList
                while (arr.size() < size) arr.add(randInt());
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int item = randInt();
                    int k = kdist(engine);
                    auto start = chrono::steady_clock::now();
                    arr.add(k, item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    arr.removeAt(arr.size() - 1);
                }
                fout << time / (double)ntries << ", ";
            }
            { // SLinkedList
                while (sll.size() < size) sll.add(randInt());
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int item = randInt();
                    int k = kdist(engine);
                    auto start = chrono::steady_clock::now();
                    sll.add(k, item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    sll.removeAt(0);
                }
                fout << time / (double)ntries << ", ";
            }
            { // DLinkedList
                while (dll.size() < size) dll.add(rand());
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int item = randInt();
                    int k = kdist(engine);
                    auto start = chrono::steady_clock::now();
                    dll.add(k, item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    dll.removeAt(0);
                }
                fout << time / (double)ntries << ", ";
            }
            { // BST
                while (bst.size() < size) bst.add(randInt());
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int item = items[tr];
                    auto start = chrono::steady_clock::now();
                    bst.add(item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    bst.remove(item);
                }
                fout << time / (double)ntries << ", ";
            }
            { // AVL
                while (avl.size() < size) avl.add(randInt());
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int item = items[tr];
                    auto start = chrono::steady_clock::now();
                    avl.add(item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    avl.remove(item);
                }
                fout << time / (double)ntries << endl;
            }
        }
        delete[] sizes;
        cout << "Test " << test << " done" << endl;
    }
    fout.close();


    ///////////////////////////////////////////////////////
    ////////////// Adding Vector3D objects ////////////////
    ///////////////////////////////////////////////////////
    fout.open("Vector3D_" + filename);
    fout << "size, XArrayList(ms), SLinkedList(ms), DLinkedList(ms), BST(ms), AVL(ms)" << endl;
    cout << "Adding Vector3D objects" << endl;
    for (int test = 0; test < nexec; ++test) {
        XArrayList<Vector3D> arr;
        SLinkedList<Vector3D> sll;
        DLinkedList<Vector3D> dll;
        BST<float, Vector3D*> bst;
        AVL<float, Vector3D*> avl;
        int *sizes = genIntArray(nsizes, 0, max_length);
        sort(sizes, sizes + nsizes);
        std::default_random_engine engine;
        for (int row = 0; row < nsizes; ++row) {
            int size = sizes[row];
            fout << size << ", ";
            uniform_int_distribution<int> kdist(0, size);
            uniform_real_distribution<float> idist(0, FLT_MAX);
            { // XArrayList
                while (arr.size() < size) arr.add(Vector3D(idist(engine), idist(engine), idist(engine)));
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int k = kdist(engine); Vector3D item(idist(engine), idist(engine), idist(engine));
                    auto start = chrono::steady_clock::now();
                    arr.add(k, item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    arr.removeAt(arr.size() - 1);
                }
                fout << time / (double)ntries << ", ";
            }
            { // SLinkedList
                while (sll.size() < size) sll.add(Vector3D(idist(engine), idist(engine), idist(engine)));
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int k = kdist(engine); Vector3D item(idist(engine), idist(engine), idist(engine));
                    auto start = chrono::steady_clock::now();
                    sll.add(k, item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    sll.removeAt(0);
                }
                fout << time / (double)ntries << ", ";
            }
            { // DLinkedList
                while (dll.size() < size) dll.add(Vector3D(idist(engine), idist(engine), idist(engine)));
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int k = kdist(engine); Vector3D item(idist(engine), idist(engine), idist(engine));
                    auto start = chrono::steady_clock::now();
                    dll.add(k, item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    dll.removeAt(0);
                }
                fout << time / (double)ntries << ", ";
            }
            { // BST
                while (bst.size() < size) bst.add(Vector3D(idist(engine), idist(engine), idist(engine)));
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D *data = new Vector3D(idist(engine), idist(engine), idist(engine));
                    int k = kdist(engine);
                    auto start = chrono::steady_clock::now();
                    bst.add(data->getX(), data);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                }
                fout << time / (double)ntries << ", ";
            }
            { // AVL
                while (avl.size() < size) avl.add(Vector3D(idist(engine), idist(engine), idist(engine)));
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D *data = new Vector3D(idist(engine), idist(engine), idist(engine));
                    int k = kdist(engine);
                    auto start = chrono::steady_clock::now();
                    avl.add(data->getX(), data);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                }
                fout << time / (double)ntries << endl;
            }
        }
        cout << "Test " << test << " done" << endl;
        delete[] sizes;
    }
}

void se_test(string filename, int nsizes, int nexec, int ntries, int max_length) {
    ofstream fout;

    ///////////////////////////////////////////////////////
    //////////////// Searching int items //////////////////
    ///////////////////////////////////////////////////////
    cout << "Searching int items" << endl;
    fout.open("int_" + filename);
    fout << "size, XArrayList(ms), SLinkedList(ms), DLinkedList(ms), BST(ms), AVL(ms)" << endl;
    for (int test = 0; test < nexec; ++test) {
        XArrayList<int> arr;
        SLinkedList<int> sll;
        DLinkedList<int> dll;
        BST<int, int*> bst;
        AVL<int, int*> avl;
        int *sizes = genIntArray(nsizes, 0, max_length);
        sort(sizes, sizes + nsizes);
        for (int row = 0; row < nsizes; ++row) {
            int size = sizes[row];
            fout << size << ", ";
            int *items = genIntArray(ntries, INT_MIN, INT_MAX);
            int addi[size - arr.size()];
            for (int &i : addi) i = randInt();
            { // XArrayList
                for (int i : addi) arr.add(i);
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    arr.indexOf(item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << ", ";
            }
            { // SLinkedList
                for (int i : addi) sll.add(i);
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    sll.indexOf(item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << ", ";
            }
            { // DLinkedList
                for (int i : addi) dll.add(i);
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    dll.indexOf(item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << ", ";
            }
            { // BST
                for (int i : addi) bst.add(i);
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    bst.search(item, found);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << ", ";
            }
            { // AVL
                for (int i : addi) bst.add(i);
                while (avl.size() < size) avl.add(randInt());
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    int item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    avl.search(item, found);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << endl;
            }
            delete[] items;
        }
        cout << "Test " << test << " done" << endl;
        delete[] sizes;
    }
    fout.close();

    ///////////////////////////////////////////////////////
    ///////////// Searching Vector3D objects //////////////
    ///////////////////////////////////////////////////////
    cout << "Searching Vector3D objects" << endl;
    fout.open("Vector3D_" + filename);
    fout << "size, XArrayList(ms), SLinkedList(ms), DLinkedList(ms), BST(ms), AVL(ms)" << endl;
    std::default_random_engine engine = std::default_random_engine(static_cast<long unsigned int>(time(0)));
    uniform_real_distribution<float> idist(0, FLT_MAX);
    for (int test = 0; test < nexec; ++test) {
        XArrayList<Vector3D> arr;
        SLinkedList<Vector3D> sll;
        DLinkedList<Vector3D> dll;
        BST<float, Vector3D*> bst;
        AVL<float, Vector3D*> avl;
        int *sizes = genIntArray(nsizes, 0, max_length);
        sort(sizes, sizes + nsizes);
        for (int row = 0; row < nsizes; ++row) {
            int size = sizes[row];
            fout << size << ", ";
            Vector3D addi[size - arr.size()];
            for (Vector3D &vec : addi) vec = Vector3D(idist(engine), idist(engine), idist(engine));
            Vector3D items[ntries];
            for (Vector3D &vec : items) vec = Vector3D(idist(engine), idist(engine), idist(engine));
            { // XArrayList
                for (Vector3D vec : addi) arr.add(vec);
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    arr.indexOf(item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << ", ";
            }
            { // SLinkedList
                for (Vector3D vec : addi) sll.add(vec);
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    sll.indexOf(item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << ", ";
            }
            { // DLinkedList
                for (Vector3D vec : addi) dll.add(vec);
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    dll.indexOf(item);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << ", ";
            }
            { // BST
                for (Vector3D vec : addi) bst.add(vec.getX(), new Vector3D(vec));
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    bst.search(item.getX(), found);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << ", ";
            }
            { // AVL
                for (Vector3D vec : addi) avl.add(vec.getX(), new Vector3D(vec));
                double time = 0;
                for (int tr = 0; tr < ntries; ++tr) {
                    Vector3D item = items[tr];
                    bool found;
                    auto start = chrono::steady_clock::now();
                    avl.search(item.getX(), found);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration<double,milli>(end - start).count();
                }
                time /= ntries;
                fout << time << endl;
            }
        }
        cout << "Test " << test << " done" << endl;
        delete[] sizes;
    }
}

int get_int(char** begin, char** end, const string& option, int _default){
    char** ptr = std::find(begin, end, option);
    if (ptr != end && ++ptr != end) return stoi(*ptr);
    else return _default;
}

string get_string(char** begin, char** end, const string& option, string _default){
    char** ptr = std::find(begin, end, option);
    if (ptr != end && ++ptr != end) return string(*ptr);
    else return _default;
}
bool option_exist(char** begin, char** end, const string& option){
    return std::find(begin, end, option) != end;
}

int main(int argc, char** argv){
    if (option_exist(argv, argv + argc, "-a")) {
        string filename = get_string(argv, argv + argc, "-a", "addtime.csv");
        int nsizes = get_int(argv, argv + argc, "-nsizes", 200);
        int nexec = get_int(argv, argv + argc, "-nexec", 100);
        int ntries = get_int(argv, argv + argc, "-ntries", 5);
        int max_length = get_int(argv, argv + argc, "-max_length", 1000000);
        cout << "Adding random items\n";
        cout << "--------------------------------------" << endl;
        add_test(filename, nsizes, nexec, ntries, max_length);
    }
    if (option_exist(argv, argv + argc, "-s")) {
        string filename = get_string(argv, argv + argc, "-s", "setime.csv");
        int nsizes = get_int(argv, argv + argc, "-nsizes", 200);
        int nexec = get_int(argv, argv + argc, "-nexec", 100);
        int ntries = get_int(argv, argv + argc, "-ntries", 5);
        int max_length = get_int(argv, argv + argc, "-max_length", 1000000);
        se_test(filename, nsizes, nexec, ntries, max_length); 
    }
}