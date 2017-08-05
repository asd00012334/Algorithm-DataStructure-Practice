#ifndef _VECTOR_
#define _VECTOR_
#include <iostream>
#include <cstdio>
#include <exception>
#include "Algorithm.hpp"

#define INIT_CAP 3



template<typename type>
class Vector{
    typedef type value_type;
    type* storage;
    size_t capacity;
    size_t eleNum;
public:
    Vector():eleNum(0),capacity(INIT_CAP){storage = new type[capacity];}
    Vector(size_t iniSize):
        eleNum(iniSize),capacity(3*iniSize+1),storage(new type[3*iniSize+1]){}
    Vector(size_t iniSize, type const& init):
        eleNum(iniSize),capacity(3*iniSize+1),storage(new type[3*iniSize+1]){
        for(size_t cnt=0;cnt<iniSize;++cnt)
            storage[cnt]=init;
    }
    ~Vector(){delete[] storage;}
    void push_back(type const& element){
        if(eleNum+1>capacity/2){
            capacity = capacity*2+1;
            type* temp = new type[capacity];
            for(int cnt=0;cnt<eleNum;cnt++)
                temp[cnt]=storage[cnt];
            delete[] storage;
            storage=temp;
        }
        storage[eleNum++]=element;
        return;
    }

    inline type& operator[](size_t idx){return storage[idx];}
    inline type& at(size_t idx){
        if(idx>=eleNum) throw std::exception();
        return storage[idx];
    }
    inline type& back(){return storage[eleNum-1];}
    inline type& front(){return storage[0];}
    inline size_t size(){return eleNum;}

    void pop_back(){
        if(!eleNum) throw std::exception();
        if(eleNum-1<capacity/4){
            capacity=capacity/2+1;
            type* temp = new type[capacity];
            for(int cnt=0;cnt<eleNum;cnt++)
                temp[cnt]=storage[cnt];
            delete[] storage;
            storage=temp;
        }
        --eleNum;
        return;
    }

    void resize(size_t newSize){
        if(newSize<capacity/4||newSize>capacity/2){
            capacity = newSize*3+1;
            type* temp = new type[capacity];
            for(int cnt=0;cnt<eleNum;cnt++)
                temp[cnt]=storage[cnt];
            delete[] storage;
            storage=temp;
        }
        eleNum=newSize;
        return;
    }

    inline Vector& swap(Vector& right){
        swap(capacity,right.capacity);
        swap(eleNum,right.eleNum);
        swap(storage,right.storage);
        return *this;
    }

    Vector& operator=(Vector const& right){
        resize(right.eleNum);
        for(int cnt=0;cnt<eleNum;cnt++)
            storage[cnt]=right.storage[cnt];
        return *this;
    }

    inline bool empty()const{return eleNum==0;}

    class iterator{
        type* ptr;
    public:
        iterator():ptr(NULL){}
        iterator(type* ptr):ptr(ptr){}
        inline type& operator[](int n){return ptr[n];}
        inline iterator operator+(int n){return iterator(ptr+n);}
        inline iterator operator-(int n){return iterator(ptr-n);}
        inline friend int operator-(iterator const& left, iterator const& right){return left.ptr-right.ptr;}
        inline iterator& operator=(iterator const& right){
            ptr=right.ptr;
            return *this;
        }
        inline iterator& operator++(){
            ++ptr;
            return *this;
        }
        inline iterator operator++(int n){return iterator(ptr++);}
        inline iterator& operator--(){
            --ptr;
            return *this;
        }
        inline iterator operator--(int n){return iterator(ptr--);}
    };
    class reverse_iterator{
        type* ptr;
    public:
        reverse_iterator():ptr(NULL){}
        reverse_iterator(type* ptr):ptr(ptr){}
        inline type& operator[](int n){return *(ptr-n);}
        inline reverse_iterator operator+(int n){return reverse_iterator(ptr-n);}
        inline reverse_iterator operator-(int n){return reverse_iterator(ptr+n);}
        inline friend int operator-(iterator const& left, iterator const& right){return right.ptr-left.ptr;}
        inline reverse_iterator& operator=(reverse_iterator const& right){
            ptr=right.ptr;
            return *this;
        }
        inline reverse_iterator& operator++(){
            --ptr;
            return *this;
        }
        inline reverse_iterator operator++(int n){return reverse_iterator(ptr--);}
        inline reverse_iterator& operator--(){
            ++ptr;
            return *this;
        }
        inline reverse_iterator operator--(int n){return reverse_iterator(ptr++);}
    };

    inline iterator begin(){return iterator(storage);}
    inline iterator end(){return iterator(storage+eleNum);}
    inline reverse_iterator rbegin(){return reverse_iterator(storage+eleNum-1);}
    inline reverse_iterator rend(){return reverse_iterator(storage-1);}

    void clear(){resize(0);}

};


#endif // _VECTOR_
