/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphTestASSIGN.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 9:47 AM
 */

#ifndef GRAPHTESTASSIGN_H
#define GRAPHTESTASSIGN_H

#include "testassignments/commons.h"


////////////////////////////////////////////////////////////////////////////////
// Testcases for UGraphModel
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): size, empty, clear, contains"){
    UGraphModel<int> model(&comparator<int>, &vertex2str);
    REQUIRE(model.size() == 0);
    REQUIRE(model.empty() == true);
    
    int size = 1000;
    for(int v=0; v < size; v++) model.add(v);
    REQUIRE(model.size() == size);
    REQUIRE(model.empty() == false);
    for(int v=0; v < size; v++) REQUIRE(model.contains(v) == true);
    
    model.clear();
    REQUIRE(model.size() == 0);
    REQUIRE(model.empty() == true);
    for(int v=0; v < size; v++) REQUIRE(model.contains(v) == false);
}

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => degrees"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //do assertion
        vector<int> outdeg_exp = links.sumrows();
        vector<int> inpdeg_exp = links.sumcols();
        for(int v=0; v <size; v++){
            int inpdeg = model.inDegree(v);
            int outdeg = model.outDegree(v);
            REQUIRE(inpdeg == outdeg);
            REQUIRE(inpdeg == inpdeg_exp[v]);
            REQUIRE(inpdeg_exp[v] == outdeg_exp[v]);
        }
    }
}

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => weights"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        
        Matrix<float> weights(size, size, Matrix<int>::FLOAT32);
        weights.uniform(-100, 100, true, 2021, true);
        
        
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c, weights.get(r,c));
            }
        }
        //do assertion
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 )
                    REQUIRE(equal(weights.get(r,c), model.weight(r,c)) == true);
            }
        }
    }
}

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => getOutwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //do assertion
        for(int from=0; from <size; from++){
            DLinkedList<int> outward = model.getOutwardEdges(from);
            
            //assert num outwards
            int count =0;
            for(int to=0; to < size; to++) count += links.get(from, to);
            REQUIRE(count == outward.size());
            
            //assert outward
            DLinkedList<int>::Iterator it;
            for(it = outward.begin(); it != outward.end(); it++){
                int to = *it;
                REQUIRE(links.get(from, to) == 1);
            }
                
        }
    }
}

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => getInwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //do assertion
        for(int to=0; to <size; to++){
            DLinkedList<int> inward = model.getInwardEdges(to);
            
            //assert num outwards
            int count =0;
            for(int from=0; from < size; from++) count += links.get(from, to);
            REQUIRE(count == inward.size());
            
            //assert outward
            DLinkedList<int>::Iterator it;
            for(it = inward.begin(); it != inward.end(); it++){
                int from = *it;
                REQUIRE(links.get(from, to) == 1);
            }
                
        }
    }
}

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => disconnect => getInwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.25*size*size;
        int *unlink_from = permutation(size, true, 2021);
        int *unlink_to = permutation(size, true, 2021);
        int removed_count = 0;
        for(int fidx=0; fidx < size; fidx++){
            for(int tidx=0; tidx < size; tidx++){
                if(removed_count >= nremoved) break;
                
                //remove <= if has connection
                int from = unlink_from[fidx];
                int to = unlink_to[tidx];
                if(links.get(from, to) > 0){
                    model.disconnect(from, to);
                    links.set(from, to, 0);
                    links.set(to, from, 0);
                    removed_count += 1;
                }
            }
        }
        
        //do assertion
        for(int to=0; to <size; to++){
            DLinkedList<int> inward = model.getInwardEdges(to);
            
            //assert num outwards
            int count =0;
            for(int from=0; from < size; from++) count += links.get(from, to);
            REQUIRE(count == inward.size());
            
            //assert outward
            DLinkedList<int>::Iterator it;
            for(it = inward.begin(); it != inward.end(); it++){
                int from = *it;
                REQUIRE(links.get(from, to) == 1);
            }
                
        }
        //delete
        delete []unlink_from;
        delete []unlink_to;
    }
}

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => disconnect => getOutwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.25*size*size;
        int *unlink_from = permutation(size, true, 2021);
        int *unlink_to = permutation(size, true, 2021);
        int removed_count = 0;
        for(int fidx=0; fidx < size; fidx++){
            for(int tidx=0; tidx < size; tidx++){
                if(removed_count >= nremoved) break;
                
                //remove <= if has connection
                int from = unlink_from[fidx];
                int to = unlink_to[tidx];
                if(links.get(from, to) > 0){
                    model.disconnect(from, to);
                    links.set(from, to, 0);
                    links.set(to, from, 0);
                    removed_count += 1;
                }
            }
        }
        
        //do assertion
        for(int from=0; from <size; from++){
            DLinkedList<int> outward = model.getOutwardEdges(from);
            
            //assert num outwards
            int count =0;
            for(int to=0; to < size; to++) count += links.get(from, to);
            REQUIRE(count == outward.size());
            
            //assert outward
            DLinkedList<int>::Iterator it;
            for(it = outward.begin(); it != outward.end(); it++){
                int to = *it;
                REQUIRE(links.get(from, to) == 1);
            }
                
        }
        //delete
        delete []unlink_from;
        delete []unlink_to;
    }
}

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => disconnect => degrees"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.25*size*size;
        int *unlink_from = permutation(size, true, 2021);
        int *unlink_to = permutation(size, true, 2021);
        int removed_count = 0;
        for(int fidx=0; fidx < size; fidx++){
            for(int tidx=0; tidx < size; tidx++){
                if(removed_count >= nremoved) break;
                
                //remove <= if has connection
                int from = unlink_from[fidx];
                int to = unlink_to[tidx];
                if(links.get(from, to) > 0){
                    model.disconnect(from, to);
                    links.set(from, to, 0);
                    links.set(to, from, 0);
                    removed_count += 1;
                }
            }
        }
        //do assertion
        vector<int> outdeg_exp = links.sumrows();
        vector<int> inpdeg_exp = links.sumcols();
        for(int v=0; v <size; v++){
            int inpdeg = model.inDegree(v);
            int outdeg = model.outDegree(v);
            
            REQUIRE(inpdeg == outdeg);
            REQUIRE(inpdeg == inpdeg_exp[v]);
            REQUIRE(inpdeg_exp[v] == outdeg_exp[v]);
        }
        //delete
        delete []unlink_from;
        delete []unlink_to;
    }
}

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => remove => degrees"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.5*size;
        int *removed_vertices = permutation(size, true, 2021);
        bool *removed_mask= new bool[size];
        for(int idx=0; idx < size; idx++) removed_mask[idx] = false;
        for(int ridx=0; ridx < nremoved; ridx++){
            int removed_vertex = removed_vertices[ridx];
            removed_mask[removed_vertex] = true;
            //remove
            for(int c=0; c < size; c++) links.set(removed_vertex, c, 0);
            for(int r=0; r < size; r++) links.set(r, removed_vertex, 0);
            model.remove(removed_vertex);
        }
        
        //do assertion
        vector<int> outdeg_exp = links.sumrows();
        vector<int> inpdeg_exp = links.sumcols();
        for(int v=0; v <size; v++){
            if(removed_mask[v] != true){
                int inpdeg = model.inDegree(v);
                int outdeg = model.outDegree(v);

                REQUIRE(inpdeg == outdeg);
                REQUIRE(inpdeg == inpdeg_exp[v]);
                REQUIRE(inpdeg_exp[v] == outdeg_exp[v]);
            }
        }
        //delete
        delete []removed_vertices;
        delete []removed_mask;
    }
}


TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => remove => getInwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.5*size;
        int *removed_vertices = permutation(size, true, 2021);
        bool *removed_mask= new bool[size];
        for(int idx=0; idx < size; idx++) removed_mask[idx] = false;
        for(int ridx=0; ridx < nremoved; ridx++){
            int removed_vertex = removed_vertices[ridx];
            removed_mask[removed_vertex] = true;
            //remove
            for(int c=0; c < size; c++) links.set(removed_vertex, c, 0);
            for(int r=0; r < size; r++) links.set(r, removed_vertex, 0);
            model.remove(removed_vertex);
        }
        
        //do assertion
        for(int to=0; to <size; to++){
            if(removed_mask[to] != true){
                DLinkedList<int> inward = model.getInwardEdges(to);

                //assert num outwards
                int count =0;
                for(int from=0; from < size; from++) count += links.get(from, to);
                REQUIRE(count == inward.size());

                //assert outward
                DLinkedList<int>::Iterator it;
                for(it = inward.begin(); it != inward.end(); it++){
                    int from = *it;
                    REQUIRE(links.get(from, to) == 1);
                }
            }
        }
        //delete
        delete []removed_vertices;
        delete []removed_mask;
    }
}
TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => remove => getOutwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.5*size;
        int *removed_vertices = permutation(size, true, 2021);
        bool *removed_mask= new bool[size];
        for(int idx=0; idx < size; idx++) removed_mask[idx] = false;
        for(int ridx=0; ridx < nremoved; ridx++){
            int removed_vertex = removed_vertices[ridx];
            removed_mask[removed_vertex] = true;
            //remove
            for(int c=0; c < size; c++) links.set(removed_vertex, c, 0);
            for(int r=0; r < size; r++) links.set(r, removed_vertex, 0);
            model.remove(removed_vertex);
        }
        
        //do assertion
        for(int from=0; from <size; from++){
            if(removed_mask[from] != true){
                DLinkedList<int> outward = model.getOutwardEdges(from);

                //assert num outwards
                int count =0;
                for(int to=0; to < size; to++) count += links.get(from, to);
                REQUIRE(count == outward.size());

                //assert outward
                DLinkedList<int>::Iterator it;
                for(it = outward.begin(); it != outward.end(); it++){
                    int to = *it;
                    REQUIRE(links.get(from, to) == 1);
                }
            }
        }
        //delete
        delete []removed_vertices;
        delete []removed_mask;
    }
}

TEST_CASE("UGraphModel<int>::connected"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build dgraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //do assertion
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 )
                    REQUIRE(model.connected(r, c) == true);
                else
                    REQUIRE(model.connected(r, c) == false);
            }
        }
    }
}

TEST_CASE("UGraphModel<int>(&vertexEQ, &vertex2tr): construction => remove => connected"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021, true);
        UGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.5*size;
        int *removed_vertices = permutation(size, true, 2021);
        bool *removed_mask= new bool[size];
        for(int idx=0; idx < size; idx++) removed_mask[idx] = false;
        for(int ridx=0; ridx < nremoved; ridx++){
            int removed_vertex = removed_vertices[ridx];
            removed_mask[removed_vertex] = true;
            //remove
            for(int c=0; c < size; c++) links.set(removed_vertex, c, 0);
            for(int r=0; r < size; r++) links.set(r, removed_vertex, 0);
            model.remove(removed_vertex);
        }
        
        //do assertion
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if((removed_mask[r] == false) && (removed_mask[c] == false)){
                    if(links.get(r,c) > 0 )
                        REQUIRE(model.connected(r, c) == true);
                    else
                        REQUIRE(model.connected(r, c) == false);
                }
            }
        }
        //delete
        delete []removed_vertices;
        delete []removed_mask;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Testcases for DGraphModel
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): size, empty, clear"){
    DGraphModel<int> model(&comparator<int>, &vertex2str);
    REQUIRE(model.size() == 0);
    REQUIRE(model.empty() == true);
    
    int size = 1000;
    for(int v=0; v < size; v++) model.add(v);
    REQUIRE(model.size() == size);
    REQUIRE(model.empty() == false);
    for(int v=0; v < size; v++) REQUIRE(model.contains(v) == true);
    
    model.clear();
    REQUIRE(model.size() == 0);
    REQUIRE(model.empty() == true);
    for(int v=0; v < size; v++) REQUIRE(model.contains(v) == false);
}

TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => degrees"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        //Build dgraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //do assertion
        vector<int> outdeg_exp = links.sumrows();
        vector<int> inpdeg_exp = links.sumcols();
        for(int v=0; v <size; v++){
            int inpdeg = model.inDegree(v);
            int outdeg = model.outDegree(v);
            REQUIRE(inpdeg == inpdeg_exp[v]);
            REQUIRE(outdeg == outdeg_exp[v]);
        }
    }
}

TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => weights"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        
        Matrix<float> weights(size, size, Matrix<int>::FLOAT32);
        weights.uniform(-100, 100, true, 2021, false);
        
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c, weights.get(r,c));
            }
        }
        //do assertion
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 )
                    REQUIRE(equal(weights.get(r,c), model.weight(r,c)) == true);
            }
        }
    }
}


TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => getOutwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build dgraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //do assertion
        for(int from=0; from <size; from++){
            DLinkedList<int> outward = model.getOutwardEdges(from);
            
            //assert num outwards
            int count =0;
            for(int to=0; to < size; to++) count += links.get(from, to);
            REQUIRE(count == outward.size());
            
            //assert outward
            DLinkedList<int>::Iterator it;
            for(it = outward.begin(); it != outward.end(); it++){
                int to = *it;
                REQUIRE(links.get(from, to) == 1);
            }
                
        }
    }
}

TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => getInwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build dgraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }

        //do assertion
        for(int to=0; to < size; to++){
            DLinkedList<int> inward = model.getInwardEdges(to);
            
            //assert num inwards
            int count =0;
            for(int from=0; from < size; from++) count += links.get(from, to);
            REQUIRE(count == inward.size());
            
            //assert inward
            DLinkedList<int>::Iterator it;
            for(it = inward.begin(); it != inward.end(); it++){
                int from = *it;
                REQUIRE(links.get(from, to) == 1);
            }
                
        }
    }
}

TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => disconnect => getInwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.25*size*size;
        int *unlink_from = permutation(size, true, 2021);
        int *unlink_to = permutation(size, true, 2021);
        int removed_count = 0;
        for(int fidx=0; fidx < size; fidx++){
            for(int tidx=0; tidx < size; tidx++){
                if(removed_count >= nremoved) break;
                
                //remove <= if has connection
                int from = unlink_from[fidx];
                int to = unlink_to[tidx];
                if(links.get(from, to) > 0){
                    model.disconnect(from, to);
                    links.set(from, to, 0);
                    removed_count += 1;
                }
            }
        }
        
        //do assertion
        for(int to=0; to <size; to++){
            DLinkedList<int> inward = model.getInwardEdges(to);
            
            //assert num outwards
            int count =0;
            for(int from=0; from < size; from++) count += links.get(from, to);
            REQUIRE(count == inward.size());
            
            //assert outward
            DLinkedList<int>::Iterator it;
            for(it = inward.begin(); it != inward.end(); it++){
                int from = *it;
                REQUIRE(links.get(from, to) == 1);
            }
                
        }
        //delete
        delete []unlink_from;
        delete []unlink_to;
    }
}

TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => disconnect => getOutwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.25*size*size;
        int *unlink_from = permutation(size, true, 2021);
        int *unlink_to = permutation(size, true, 2021);
        int removed_count = 0;
        for(int fidx=0; fidx < size; fidx++){
            for(int tidx=0; tidx < size; tidx++){
                if(removed_count >= nremoved) break;
                
                //remove <= if has connection
                int from = unlink_from[fidx];
                int to = unlink_to[tidx];
                if(links.get(from, to) > 0){
                    model.disconnect(from, to);
                    links.set(from, to, 0);
                    removed_count += 1;
                }
            }
        }
        
        //do assertion
        for(int from=0; from <size; from++){
            DLinkedList<int> outward = model.getOutwardEdges(from);
            
            //assert num outwards
            int count =0;
            for(int to=0; to < size; to++) count += links.get(from, to);
            REQUIRE(count == outward.size());
            
            //assert outward
            DLinkedList<int>::Iterator it;
            for(it = outward.begin(); it != outward.end(); it++){
                int to = *it;
                REQUIRE(links.get(from, to) == 1);
            }
                
        }
        //delete
        delete []unlink_from;
        delete []unlink_to;
    }
}


TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => disconnect => degrees"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.25*size*size;
        int *unlink_from = permutation(size, true, 2021);
        int *unlink_to = permutation(size, true, 2021);
        int removed_count = 0;
        for(int fidx=0; fidx < size; fidx++){
            for(int tidx=0; tidx < size; tidx++){
                if(removed_count >= nremoved) break;
                
                //remove <= if has connection
                int from = unlink_from[fidx];
                int to = unlink_to[tidx];
                if(links.get(from, to) > 0){
                    model.disconnect(from, to);
                    links.set(from, to, 0);
                    removed_count += 1;
                }
            }
        }
        //do assertion
        vector<int> outdeg_exp = links.sumrows();
        vector<int> inpdeg_exp = links.sumcols();
        for(int v=0; v <size; v++){
            int inpdeg = model.inDegree(v);
            int outdeg = model.outDegree(v);
            REQUIRE(inpdeg == inpdeg_exp[v]);
            REQUIRE(outdeg == outdeg_exp[v]);
        }
        //delete
        delete []unlink_from;
        delete []unlink_to;
    }
}

TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => remove => degrees"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build dgraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.5*size;
        int *removed_vertices = permutation(size, true, 2021);
        bool *removed_mask= new bool[size];
        for(int idx=0; idx < size; idx++) removed_mask[idx] = false;
        for(int ridx=0; ridx < nremoved; ridx++){
            int removed_vertex = removed_vertices[ridx];
            removed_mask[removed_vertex] = true;
            //remove
            for(int c=0; c < size; c++) links.set(removed_vertex, c, 0);
            for(int r=0; r < size; r++) links.set(r, removed_vertex, 0);
            model.remove(removed_vertex);
        }
        
        //do assertion
        vector<int> outdeg_exp = links.sumrows();
        vector<int> inpdeg_exp = links.sumcols();
        for(int v=0; v <size; v++){
            if(removed_mask[v] != true){
                int inpdeg = model.inDegree(v);
                int outdeg = model.outDegree(v);
                REQUIRE(inpdeg == inpdeg_exp[v]);
                REQUIRE(outdeg == outdeg_exp[v]);
            }
        }
        //delete
        delete []removed_vertices;
        delete []removed_mask;
    }
}

TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => remove => getInwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build dgraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.5*size;
        int *removed_vertices = permutation(size, true, 2021);
        bool *removed_mask= new bool[size];
        for(int idx=0; idx < size; idx++) removed_mask[idx] = false;
        for(int ridx=0; ridx < nremoved; ridx++){
            int removed_vertex = removed_vertices[ridx];
            removed_mask[removed_vertex] = true;
            //remove
            for(int c=0; c < size; c++) links.set(removed_vertex, c, 0);
            for(int r=0; r < size; r++) links.set(r, removed_vertex, 0);
            model.remove(removed_vertex);
        }
        
        //do assertion
        for(int to=0; to <size; to++){
            if(removed_mask[to] != true){
                DLinkedList<int> inward = model.getInwardEdges(to);

                //assert num outwards
                int count =0;
                for(int from=0; from < size; from++) count += links.get(from, to);
                REQUIRE(count == inward.size());

                //assert outward
                DLinkedList<int>::Iterator it;
                for(it = inward.begin(); it != inward.end(); it++){
                    int from = *it;
                    REQUIRE(links.get(from, to) == 1);
                }
            }
        }
        //delete
        delete []removed_vertices;
        delete []removed_mask;
    }
}
TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => remove => getOutwardEdges"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.5*size;
        int *removed_vertices = permutation(size, true, 2021);
        bool *removed_mask= new bool[size];
        for(int idx=0; idx < size; idx++) removed_mask[idx] = false;
        for(int ridx=0; ridx < nremoved; ridx++){
            int removed_vertex = removed_vertices[ridx];
            removed_mask[removed_vertex] = true;
            //remove
            for(int c=0; c < size; c++) links.set(removed_vertex, c, 0);
            for(int r=0; r < size; r++) links.set(r, removed_vertex, 0);
            model.remove(removed_vertex);
        }
        
        //do assertion
        for(int from=0; from <size; from++){
            if(removed_mask[from] != true){
                DLinkedList<int> outward = model.getOutwardEdges(from);

                //assert num outwards
                int count =0;
                for(int to=0; to < size; to++) count += links.get(from, to);
                REQUIRE(count == outward.size());

                //assert outward
                DLinkedList<int>::Iterator it;
                for(it = outward.begin(); it != outward.end(); it++){
                    int to = *it;
                    REQUIRE(links.get(from, to) == 1);
                }
            }
        }
        //delete
        delete []removed_vertices;
        delete []removed_mask;
    }
}
TEST_CASE("DGraphModel<int>(&vertexEQ, &vertex2tr): construction => remove => connected"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build ugraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //remove 50%
        int nremoved = 0.5*size;
        int *removed_vertices = permutation(size, true, 2021);
        bool *removed_mask= new bool[size];
        for(int idx=0; idx < size; idx++) removed_mask[idx] = false;
        for(int ridx=0; ridx < nremoved; ridx++){
            int removed_vertex = removed_vertices[ridx];
            removed_mask[removed_vertex] = true;
            //remove
            for(int c=0; c < size; c++) links.set(removed_vertex, c, 0);
            for(int r=0; r < size; r++) links.set(r, removed_vertex, 0);
            model.remove(removed_vertex);
        }
        
        //do assertion
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if((removed_mask[r] == false) && (removed_mask[c] == false)){
                    if(links.get(r,c) > 0 )
                        REQUIRE(model.connected(r, c) == true);
                    else
                        REQUIRE(model.connected(r, c) == false);
                }
            }
        }
        //delete
        delete []removed_vertices;
        delete []removed_mask;
    }
}


TEST_CASE("DGraphModel<int>::connected"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build dgraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //do assertion
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 )
                    REQUIRE(model.connected(r, c) == true);
                else
                    REQUIRE(model.connected(r, c) == false);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
// Testcases for AbstractGraph
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("AbstractGraph<int>::vertices"){
    int sizes[] = {10, 100};
    for(int size: sizes){
        Matrix<int> links(size, size, Matrix<int>::INT32);
        links.binomial(0.6, true, 2021);
        DGraphModel<int> model(&comparator<int>, &vertex2str);
        
        //Build dgraph
        for(int v=0; v < size; v++) model.add(v);
        for(int r=0; r < size; r++){
            for(int c=0; c < size; c++){
                if(links.get(r,c) > 0 ) model.connect(r, c);
            }
        }
        //
        DLinkedList<int> vertices = model.vertices();
        REQUIRE(vertices.size() == size);
        DLinkedList<int>::Iterator it;
        int v;
        for(v = 0, it = vertices.begin(); it != vertices.end(); it++, v++)
            REQUIRE(*it == v);
    }
}


//////////////////////////////////////////////////////////////////////
// Polymorphism
//////////////////////////////////////////////////////////////////////
TEST_CASE("IGraph<int>(&vertexEQ, &vertex2tr): size, empty, clear"){
    IGraph<int>* model = new UGraphModel<int>(&comparator<int>, &vertex2str);
    REQUIRE(model->size() == 0);
    REQUIRE(model->empty() == true);
    
    int size = 1000;
    for(int v=0; v < size; v++) model->add(v);
    REQUIRE(model->size() == size);
    REQUIRE(model->empty() == false);
    
    model->clear();
    REQUIRE(model->size() == 0);
    REQUIRE(model->empty() == true);
    
    delete model;
    
    //
    model = new DGraphModel<int>(&comparator<int>, &vertex2str);
    REQUIRE(model->size() == 0);
    REQUIRE(model->empty() == true);
    
    for(int v=0; v < size; v++) model->add(v);
    REQUIRE(model->size() == size);
    REQUIRE(model->empty() == false);
    
    model->clear();
    REQUIRE(model->size() == 0);
    REQUIRE(model->empty() == true);
    
    delete model;
}

//TOPOSORT

TEST_CASE( "TopoSort with DGraphModel" ) {
    int nv = 10, ne = 14;
    char vertex[]   = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char from[]     = {'0', '0', '1', '3', '3', '3', '3', '4', '6', '6', '6', '8', '8', '9'};
    char to[]       = {'1', '5', '7', '2', '4', '7', '8', '8', '0', '1', '2', '2', '7', '4'};
    char bfs_exp[]  = {'3', '6', '9', '0', '4', '1', '5', '8', '2', '7'};
    char dfs_exp[]  = {'3', '6', '0', '5', '1', '9', '4', '8', '2', '7'};

    DGraphModel<char> model(&comparator<char>, &vertex2str);
    REQUIRE(model.size() == 0);
    REQUIRE(model.empty() == true);
    
    for(int v=0; v < nv; v++) model.add(vertex[v]);
    for(int e=0; e < ne; e++) model.connect(from[e], to[e]);
    REQUIRE(model.size() == nv);
    
    TopoSorter<char> sorter(&model, &hash_code);
    DLinkedList<char> bfs = sorter.sort(TopoSorter<char>::BFS);
    DLinkedList<char>::Iterator it;
    
    int v= 0;
    for(it = bfs.begin(); it != bfs.end(); it++){
        REQUIRE(*it == bfs_exp[v++]);
    }
    
    v = 0;
    DLinkedList<char> dfs = sorter.sort(TopoSorter<char>::DFS);
    for(it = dfs.begin(); it != dfs.end(); it++){
        REQUIRE(*it == dfs_exp[v++]);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Testcases for Edge
////////////////////////////////////////////////////////////////////////////////

IGraph<char>* burglary_earthquake(){
    char vertices[] = {B, E, A, M, J};
    Edge<char> edges[] = {
        Edge<char>(B, A),
        Edge<char>(E, A),
        Edge<char>(A, M),
        Edge<char>(A, J)
    };
    return DGraphModel<char>::create(
            vertices, sizeof(vertices)/sizeof(char),
            edges, sizeof(edges)/sizeof(Edge<char>),
            &comparator<char>, &vertex2str);
}


TEST_CASE("Edge + Toposorter"){
    IGraph<char>* model = burglary_earthquake();
    TopoSorter<char> sorter(dynamic_cast<DGraphModel<char>*>(model), &hash_code);
    DLinkedList<char> list = sorter.sort();
    REQUIRE(list.size() ==  model->size());
    delete model;
}
#endif /* GRAPHTESTASSIGN_H */

