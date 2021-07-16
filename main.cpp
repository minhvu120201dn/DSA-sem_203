#include <iostream>
#include <iomanip>
using namespace std;

#include "graph/UGraphModel.h"
#include "graph/DGraphModel.h"

bool vertexEQ(char& lhs, char& rhs){
    return lhs == rhs;
}
string vertex2str(char& item){
    return std::to_string(item);
}

IGraph<char>* create_graph_1(){
    char vertices[] = {'A', 'X', 'G', 'H', 'P', 'E', 'Y', 'M', 'J'};
    Edge<char> edges[] = {
        Edge<char>('A', 'X'),
        Edge<char>('X', 'G'),
        Edge<char>('X', 'H'),
        Edge<char>('G', 'H'),
        Edge<char>('G', 'P'),
        Edge<char>('H', 'P'),
        Edge<char>('H', 'E'),
        Edge<char>('E', 'M'),
        Edge<char>('E', 'Y'),
        Edge<char>('Y', 'M'),
        Edge<char>('M', 'J')
    };
    IGraph<char> *graph = new DGraphModel<char>(&vertexEQ, &vertex2str);
    for(char v: vertices) graph->add(v);
    for(Edge<char> edge: edges) graph->connect(edge.from, edge.to);
    return graph;
}

int main() {
    create_graph_1();
}