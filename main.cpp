#include <iostream>
#include <iomanip>
using namespace std;

#include "graph/UGraphModel.h"
#include "graph/DGraphModel.h"
#include "graph/TopoSorter.h"

char    A='A', B='B', C='C', D='D', E='E', \
        F='F', G='G', H='H', I='I', J='J', \
        K='K', L='L', M='M', N='N', O='O', \
        P='P', Q='Q', R='R', S='S', T='T', \
        U='U', V='V', X='X', Y='Y', Z='Z';
template <typename T>
struct Edge {
    T from, to;
    int weight;
    Edge(T from = 0, T to = 0, int weight = 0) : from(from), to(to), weight(weight) {}
};

int hash_code(char& key, int size){
    return (int)key % size;
}

bool vertexEQ(char& lhs, char& rhs){
    return lhs == rhs;
}
string vertex2str(char& item){
    return std::to_string(item);
}

void bft(IGraph<char>* model, char start){
    DLinkedList<char> results;
    
    Queue<char> open; //contain nodes TO BE processed in future
    XHashMap<char, char> inopen(&hash_code);
    XHashMap<char, char> inclose(&hash_code); //contains vertices that have been processed
    
    open.push(start);
    inopen.put(start, start);
    
    while(!open.empty()){
        char vertex = open.pop();
        inopen.remove(vertex);
        //process
        results.add(vertex); //save it to results and then process later
        inclose.put(vertex, vertex);
        
        //generate children + push to open
        DLinkedList<char> children = model->getOutwardEdges(vertex);
        DLinkedList<char>::Iterator it;
        for(it = children.begin(); it != children.end(); it++){
            char child = *it;
            if(inopen.containsKey(child)) continue;
            if(inclose.containsKey(child)) continue;
            
            open.push(child);
            inopen.put(child, child);
        }
    }
    
    //
    results.println();
}

void dft(IGraph<char>* model, char start){
    DLinkedList<char> results;
    
    Stack<char> open; //contain nodes TO BE processed in future
    XHashMap<char, char> inopen(&hash_code);
    XHashMap<char, char> inclose(&hash_code); //contains vertices that have been processed
    
    open.push(start);
    inopen.put(start, start);
    
    while(!open.empty()){
        char vertex = open.pop();
        inopen.remove(vertex);
        //process
        results.add(vertex); //save it to results and then process later
        inclose.put(vertex, vertex);
        
        //generate children + push to open
        DLinkedList<char> children = model->getOutwardEdges(vertex);
        DLinkedList<char>::Iterator it;
        for(it = children.begin(); it != children.end(); it++){
            char child = *it;
            if(inclose.containsKey(child)) continue;
            if(inopen.containsKey(child)){
                open.remove(child);
                open.push(child);
                continue;
            }
            
            open.push(child);
            inopen.put(child, child);
        }
    }
    
    //
    results.println();    
}

DGraphModel<char>* graph_in_picture(){
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    Edge<char> edges[] = {
        Edge<char>('A', 'B'),
        Edge<char>('A', 'D'),
        Edge<char>('B', 'D'),
        Edge<char>('B', 'F'),
        Edge<char>('C', 'D'),
        Edge<char>('C', 'E'),
        Edge<char>('D', 'F'),
        Edge<char>('E', 'F'),
        Edge<char>('F', 'H'),
        Edge<char>('G', 'F'),
        Edge<char>('G', 'H')
    };
    DGraphModel<char> *graph = new DGraphModel<char>(&vertexEQ, &vertex2str);
    for(char v: vertices) graph->add(v);
    for(Edge<char> edge: edges) graph->connect(edge.from, edge.to);
    return graph;
}

DGraphModel<char>* dsaframework(){
    char vertices[] = {A, B, C, D, E, F, G, H, I, J, K};
    Edge<char> edges[] = {
        Edge<char>(A, B),
        Edge<char>(A, C),
        Edge<char>(A, D),
        Edge<char>(D, E),
        Edge<char>(D, F),
        Edge<char>(D, H),
        Edge<char>(D, I),
        Edge<char>(G, E),
        Edge<char>(G, F),
        Edge<char>(H, J),
        Edge<char>(I, J),
        Edge<char>(J, K)
    };
    DGraphModel<char> *graph = new DGraphModel<char>(&vertexEQ, &vertex2str);
    for(char v: vertices) graph->add(v);
    for(Edge<char> edge: edges) graph->connect(edge.from, edge.to);
    return graph;
}

int main() {
    TopoSorter<char> topo_sorter(dsaframework());
    topo_sorter.dfsSort().println();
}