/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
#include "stacknqueue/PriorityQueue.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class UGraphModel: public AbstractGraph<T>{
private:
public:
    //class UGraphAlgorithm;
    //friend class UGraphAlgorithm;
    
    UGraphModel(
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
        if (start->equals(dest)) {
            start->connect(start, weight);
        }
        else {
            start->connect(dest, weight);
            dest->connect(start, weight);
        }
    }
    void disconnect(T from, T to){
        //YOUR CODE HERE
        typename AbstractGraph<T>::VertexNode *start = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode *dest = this->getVertexNode(to);
        if (!start) throw VertexNotFoundException(this->vertex2Str(*start));
        if (!dest) throw VertexNotFoundException(this->vertex2Str(*dest));
        if (start->equals(dest)) {
            start->removeTo(start);
        }
        else {
            start->removeTo(dest);
            dest->removeTo(start);
        }
    }
    void remove(T vertex){
        //YOUR CODE HERE
        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator node = this->nodeList.begin();
        while (node != this->nodeList.end() && !this->vertexEQ((*node)->getVertex(), vertex)) ++node;
        if (!(node != this->nodeList.end())) throw VertexNotFoundException(this->vertex2Str(**node));

        for (typename DLinkedList<typename AbstractGraph<T>::Edge*>::Iterator it = (*node)->adList.begin(); it != (*node)->adList.end(); ++it)
            if ((*it)->to->vertex != (*node)->vertex)
                (*it)->to->removeTo(*node), --(*it)->to->inDegree_;
        node.remove();
    }

    static UGraphModel<T> *create(T *vertexList, int vertexNum, Edge<T> *edgeList, int edgeNum, bool (*vertexEQ)(T&, T&), string (*vertex2str)(T&)) {
        UGraphModel<T> *graph = new UGraphModel(vertexEQ, vertex2str);
        for (int i = 0; i < vertexNum; ++i) graph->add(vertexList[i]);
        for (int i = 0; i < edgeNum; ++i) graph->connect(edgeList[i].from, edgeList[i].to, edgeList[i].weight);
        return graph;
    }
};



#endif /* UGRAPHMODEL_H */

