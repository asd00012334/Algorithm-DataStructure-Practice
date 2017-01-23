#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_
#include <iostream>
#include <cstdio>
#include <exception>
#include "Algorithm.hpp"
#include "Vector.hpp"

template<typename type>
class PriorityQueue{
private:
    Vector<type> storage;
public:
    size_t size(){return storage.size();}
    void push(type ins){
        int insIndex;
        insIndex = storage.size();
        storage.push_back(ins);
        for(;storage[insIndex]<storage[(insIndex-1)/2]&&insIndex;insIndex=(insIndex-1)/2)
            ::swap(storage[(insIndex-1)/2],storage[insIndex]);
    }
    type const& top(){return storage.at(0);}
    void pop(){
        if(storage.empty()) throw std::exception();
        ::swap(storage.front(),storage.back());
        storage.pop_back();
        int curIndex = 0;
        while(1){
            if(2*curIndex+2<storage.size()){
                if(storage[2*curIndex+1]<storage[curIndex] || storage[2*curIndex+2]<storage[curIndex])
                    if(storage[2*curIndex+1]<storage[2*curIndex+2]){
                        ::swap(storage[curIndex],storage[2*curIndex+1]);
                        curIndex = 2*curIndex+1;
                    }
                    else{
                        ::swap(storage[curIndex],storage[2*curIndex+2]);
                        curIndex = 2*curIndex+2;
                    }
                    else break;
            }
            else if(2*curIndex+1<storage.size() && storage[2*curIndex+1]<storage[curIndex]){
                ::swap(storage[curIndex],storage[2*curIndex+1]);
                curIndex = 2*curIndex+1;
            }
            else break;
        }
    }
    bool empty(){return storage.empty();}
    void swap(PriorityQueue<type>& right){storage.swap(right.storage);}
};

#endif // _PRIORITY_QUEUE_
