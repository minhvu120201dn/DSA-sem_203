
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

#include "list/XArrayList.h"
#include "list/SLinkedList.h"
#include "list/DLinkedList.h"
#include "list/IList.h"
#include "util/ArrayLib.h"
#include <algorithm>


/*
NOTE:
  * SHOULD define other functions to support the implementation of "meter"
  * Parameters: read the explanation presented above
*/
void meter(IList<int>* plist, string csvfile, int* ptr_sizes, int nsizes, int nexec=10, int ntries=10){
    //YOUR CODE HERE
    ofstream fout(csvfile);
    fout << "size, addfirst(ms), addlast(ms), addrandpos(ms), removefirst(ms), removelast(ms), removerandpos(ms), getrandpos(ms)\n";
    cout << "index/nsizes:\t" << setw(6) << 'n' << "\t->" << setw(14) << "add(0,*)," << setw(14) << "add(*)," << setw(14) << "add(k,*)," << setw(14) << "removeAt(0)," << setw(15) << "removeAt(n-1)," << setw(14) << "removeAt(k)," << setw(13) << "get(k)" << endl;
    std::default_random_engine engine = std::default_random_engine(static_cast<long unsigned int>(time(0)));
    for (int test = 0; test < nsizes; ++test) {
        int size = ptr_sizes[test];
        fout << size << ", ";
        // plist->size() == size
        while (plist->size() < size)
            plist->add(plist->size());
        while (plist->size() > size)
            plist->removeAt(plist->size()-1);
        if (!(test % 10)) cout << '[' << setw(2) << test << "/100]:\t" << setw(6) << size << "\t->";
        /////////////////////////////////////////////////////////////////
        ///////////////////////// EXPERIMENT ////////////////////////////
        /////////////////////////////////////////////////////////////////
        { // addfirst
            double time = 0;
            for (int exec = 0; exec < nexec; exec++) {
                auto start = chrono::steady_clock::now();
                plist->add(0,size);
                auto end = chrono::steady_clock::now();
                time += chrono::duration <double, milli> (end - start).count();
                plist->removeAt(0);
            }
            time /= nexec;
            fout << time << ", ";
            if (!(test % 10)) cout << fixed << setw(13) << setprecision(8) << time << ',';
        }
        { // addlast
            double time = 0;
            for (int exec = 0; exec < nexec; exec++) {
                auto start = chrono::steady_clock::now();
                plist->add(plist->size(),size);
                auto end = chrono::steady_clock::now();
                time += chrono::duration <double, milli> (end - start).count();
                plist->removeAt(plist->size()-1);
            }
            time /= nexec;
            fout << time << ", ";
            if (!(test % 10)) cout << fixed << setw(13) << setprecision(8) << time << ',';
        }
        { // addrandpos
            uniform_int_distribution<int> dist(0,size);
            double time = 0;
            for (int exec = 0; exec < nexec; exec++) {
                for (int tr = 0; tr < ntries; tr++) {
                    int k = dist(engine);
                    auto start = chrono::steady_clock::now();
                    plist->add(k,size);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    plist->removeAt(k);
                }
            }
            time /= nexec * ntries;
            fout << time << ", ";
            if (!(test % 10)) cout << fixed << setw(13) << setprecision(8) << time << ',';
        }
        { // removefirst
            double time = 0;
            for (int exec = 0; exec < nexec; exec++) {
                auto start = chrono::steady_clock::now();
                plist->removeAt(0);
                auto end = chrono::steady_clock::now();
                time += chrono::duration <double, milli> (end - start).count();
                plist->add(0,0);
            }
            time /= nexec;
            fout << time << ", ";
            if (!(test % 10)) cout << fixed << setw(13) << setprecision(8) << time << ',';
        }
        { // removelast
            double time = 0;
            for (int exec = 0; exec < nexec; exec++) {
                auto start = chrono::steady_clock::now();
                plist->removeAt(plist->size()-1);
                auto end = chrono::steady_clock::now();
                time += chrono::duration <double, milli> (end - start).count();
                plist->add(plist->size());
            }
            time /= nexec;
            fout << time << ", ";
            if (!(test % 10)) cout << fixed << setw(14) << setprecision(8) << time << ',';
        }
        { // removerandpos
            uniform_int_distribution<int> dist(0,size-1);
            double time = 0;
            for (int exec = 0; exec < nexec; exec++) {
                for (int tr = 0; tr < ntries; tr++) {
                    int k = dist(engine);
                    auto start = chrono::steady_clock::now();
                    plist->removeAt(k);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                    plist->add(k,k);
                }
            }
            time /= nexec * ntries;
            fout << time << ", ";
            if (!(test % 10)) cout << fixed << setw(13) << setprecision(8) << time << ',';
        }
        { // getrandpos
            uniform_int_distribution<int> dist(0,size-1);
            double time = 0;
            for (int exec = 0; exec < nexec; exec++) {
                for (int tr = 0; tr < ntries; tr++) {
                    int k = dist(engine);
                    auto start = chrono::steady_clock::now();
                    plist->get(k);
                    auto end = chrono::steady_clock::now();
                    time += chrono::duration <double, milli> (end - start).count();
                }
            }
            time /= nexec * ntries;
            fout << time << '\n';
            if (!(test % 10)) cout << fixed << setw(13) << setprecision(8) << time << endl;
        }
    }
    fout.close();
}

/////////////////////////////////////////////////////////////////////////////
// YOUR ARE NOT REQUIRED TO CHANGE THE FOLLOWING FUNCTIONS
/////////////////////////////////////////////////////////////////////////////

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
    if(option_exist(argv, argv+argc, "-h")){
        cout << "Show help" << endl;
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////////
    int nsizes, nexec, max_length, ntries;
    XArrayList<int> alist;
    SLinkedList<int> slist;
    DLinkedList<int> dlist;

    nsizes = get_int(argv, argv+argc, "-nsizes", 50);
    nexec = get_int(argv, argv+argc, "-nexec", 20);
    max_length = get_int(argv, argv+argc, "-max_length", 1000);
    ntries = get_int(argv, argv+argc, "-ntries", 10);
    int* ptr_sizes = genIntArray(nsizes, 1, max_length);
    
    //cout << nsizes << ", " << nexec << ", " << max_length << ", " << ntries << endl;
    if(option_exist(argv, argv+argc, "-a")){
        cout << endl;
        cout << "XArrayList: Time measurement" << endl;
        cout << string(80, '-') << endl;

        string filename = get_string(argv, argv+argc, "-a", "");
        meter(&alist, filename, ptr_sizes, nsizes, nexec, ntries);
    }
    if(option_exist(argv, argv+argc, "-s")){
        cout << endl;
        cout << "SLinkedList: Time measurement" << endl;
        cout << string(80, '-') << endl;

        string filename = get_string(argv, argv+argc, "-s", "");
        meter(&slist, filename, ptr_sizes, nsizes, nexec, ntries);
    }
    if(option_exist(argv, argv+argc, "-d")){
        cout << endl;
        cout << "DLinkedList: Time measurement" << endl;
        cout << string(80, '-') << endl;
        string filename = get_string(argv, argv+argc, "-d", "");
        meter(&dlist, filename, ptr_sizes, nsizes, nexec, ntries);
    }
    
}
