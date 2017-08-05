#ifndef _DISJOINT_SET_
#define _DISJOINT_SET_
#include <iostream>
#include <cstdio>
#include "Vector.hpp"

class DisjointSet{
    int groups;
    Vector<int> storage;
    Vector<int> card;
public:
    DisjointSet():groups(0){}
    DisjointSet(int n){
        makeSet(n);
    }
    void makeSet(int n){
        groups=n;
        storage.resize(n);
        card.resize(n);
        for(int cnt=0;cnt<n;cnt++){
            storage[cnt]=cnt;
            card[cnt]=0;
        }
    }
    int findSet(int idx){
        if(storage[idx]==idx) return idx;
        return storage[idx]=findSet(storage[idx]);
    }
    void unionSet(int l, int r){
        int lHead=findSet(l);
        int rHead=findSet(r);
        if(lHead==rHead) return;
        --groups;
        storage[rHead]=lHead;
        card[lHead]+=card[rHead];
        card[rHead]=0;
    }
    bool equal(int l, int r){return findSet(l)==findSet(r);}
    int cardinality(int n){return card[findSet(n)];}
    void clear(){
        groups=0;
        storage.clear();
        card.clear();
    }
};

#endif // _DISJOINT_SET_
