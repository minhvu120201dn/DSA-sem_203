/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/XHashMap.h"
#include "stacknqueue/PriorityQueue.h"
#include "sorting/DLinkedListSE.h"


//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str){
    }
    
    void connect(T from, T to, float weight=0){
        //YOUR CODE HERE
        typename AbstractGraph<T>::VertexNode *start = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode *dest = this->getVertexNode(to);
        if (!start) throw VertexNotFoundException(this->vertex2Str(*start));
        if (!dest) throw VertexNotFoundException(this->vertex2Str(*dest));
        start->connect(dest, weight);
    }
    void disconnect(T from, T to){
        //YOUR CODE HERE
        typename AbstractGraph<T>::VertexNode *start = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode *dest = this->getVertexNode(to);
        if (!start) throw VertexNotFoundException(this->vertex2Str(*start));
        if (!dest) throw VertexNotFoundException(this->vertex2Str(*dest));
        start->removeTo(dest);
    }
    void remove(T vertex){
        //YOUR CODE HERE
        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator node = this->nodeList.begin();
        while (node != this->nodeList.end() && !this->vertexEQ((*node)->getVertex(), vertex)) ++node;
        if (!(node != this->nodeList.end())) throw VertexNotFoundException(this->vertex2Str(**node));

        for (typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator it = this->nodeList.begin(); it != this->nodeList.end(); ++it)
            (*it)->removeTo(*node);
        node.remove();
    }

    static DGraphModel<T> *create(T *vertexList, int vertexNum, Edge<T> *edgeList, int edgeNum, bool (*vertexEQ)(T&, T&), string (*vertex2str)(T&)) {
        DGraphModel<T> *graph = new DGraphModel(vertexEQ, vertex2str);
        for (int i = 0; i < vertexNum; ++i) graph->add(vertexList[i]);
        for (int i = 0; i < edgeNum; ++i) graph->connect(edgeList[i].from, edgeList[i].to, edgeList[i].weight);
        return graph;
    }
};

#endif /* DGRAPHMODEL_H */

