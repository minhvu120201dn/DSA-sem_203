/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "hash/XHashMap.h"

template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)= XHashMap<T,int>::simpleHash){
        this->graph = graph;
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0){
        if(mode == DFS) return dfsSort();
        else return bfsSort();
    }
    DLinkedList<T> bfsSort(){
        DLinkedList<T> topoOrder;
        //YOUR CODE HERE
        Queue<typename AbstractGraph<T>::VertexNode*> open; graph->pushZeroInDegreeNodes(&open);
        XHashMap<T, int> inDeg_map = this->vertex2inDegree();
        XHashMap<T, bool> in_queue = this->inQueueMap(open);
        while (!open.empty()) {
            typename AbstractGraph<T>::VertexNode *node = open.pop();
            topoOrder.add(node->getVertex());
            in_queue.get(node->getVertex()) = false;
            int num; typename AbstractGraph<T>::VertexNode **children_list = node->getChildrenNodes(num);
            for (int i = 0; i < num; ++i) {
                typename AbstractGraph<T>::VertexNode *child = children_list[i];
                int &cur_inDeg = inDeg_map.get(child->getVertex());
                bool &cur_inQ = in_queue.get(child->getVertex());
                if (cur_inDeg == 0 || cur_inQ) continue;

                --cur_inDeg;
                if (cur_inDeg == 0) open.push(child), cur_inQ = true;
            }
            delete[] children_list;
        }
        return topoOrder;
    }
    
    DLinkedList<T> dfsSort(){
        DLinkedList<T> topoOrder;
        //YOUR CODE HERE
        Stack<typename AbstractGraph<T>::VertexNode*> open; graph->pushZeroInDegreeNodes(&open);
        XHashMap<T, bool> visited = this->vertex2Visited();
        XHashMap<T, bool> in_stack = this->inStackMap(open);
        while (!open.empty()) {
            typename AbstractGraph<T>::VertexNode *node = open.peek();
            bool &top_vis = visited.get(node->getVertex());
            if (top_vis) {
                topoOrder.add(0, node->getVertex());
                open.pop();
                continue;
            }

            int num; typename AbstractGraph<T>::VertexNode **children_list = node->getChildrenNodes(num);
            for (int i = 0; i < num; ++i) {
                typename AbstractGraph<T>::VertexNode *child = children_list[i];
                bool &cur_vis = visited.get(child->getVertex());
                bool &cur_inS = in_stack.get(child->getVertex());
                if (!cur_vis && !cur_inS) open.push(child), cur_inS = true;
            }
            delete[] children_list;
            top_vis = true;
        }
        return topoOrder;
    }
protected:
    inline XHashMap<T, bool> inQueueMap(Queue<typename AbstractGraph<T>::VertexNode*> &open) {
        XHashMap<T, bool> map(this->hash_code);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            map.put(vertex, false);
            
            vertexIt++;
        }
        for (typename Queue<typename AbstractGraph<T>::VertexNode*>::Iterator it = open.front(); it != open.rear(); ++it)
            map.get((*it)->getVertex()) = true;
        return map;
    }
    inline XHashMap<T, bool> inStackMap(Stack<typename AbstractGraph<T>::VertexNode*> &open) {
        XHashMap<T, bool> map(this->hash_code);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            map.put(vertex, false);
            
            vertexIt++;
        }
        for (typename Stack<typename AbstractGraph<T>::VertexNode*>::Iterator it = open.top(); it != open.bottom(); ++it)
            map.get((*it)->getVertex()) = true;
        return map;
    }
    inline XHashMap<T, bool> vertex2Visited(){
        XHashMap<T, bool> map(this->hash_code);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            map.put(vertex, false);
            
            vertexIt++;
        }
        return map;
    }

    XHashMap<T, int> vertex2inDegree(){
        XHashMap<T, int> map(this->hash_code);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            int inDegree = this->graph->inDegree(vertex);
            map.put(vertex, inDegree);
            
            vertexIt++;
        }
        return map;
    }
    XHashMap<T, int> vertex2outDegree(){
        XHashMap<T, int> map(this->hash_code);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            int outDegree = this->graph->outDegree(vertex);
            map.put(vertex, outDegree);
            
            vertexIt++;
        }
        return map;
    }
    
    DLinkedList<T> listOfZeroInDegrees(){
        DLinkedList<T> list;
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            int inDegree = this->graph->inDegree(vertex);
            if(inDegree == 0) list.add(vertex);
            
            vertexIt++;
        }
        return list;
    }
}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

