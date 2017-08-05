#include<bits/stdc++.h>

using namespace std;

template<typename type>
class SegTree{
    inline int left(int idx){return idx*2+1;}
    inline int right(int idx){return idx*2+2;}
    int segLen;
    vector<type> storage;
    vector<bool> tags;
    type multiply(type base, int size){
        type result = base;
        --size;
        while(size){
            if(size&1) result = result+base;
            base = base+base;
            size/=2;
        }
        return result;
    }
    void pushDown(int root, int size){
        storage[left(root)] = storage[right(root)] = storage[root];
        tags[left(root)] = tags[right(root)] = true;
        storage[root] = multiply(storage[root], size);
        tags[root] = false;
    }
public:
    SegTree(){}

    template<typename iter>
    SegTree(iter begin, iter end){
        build(begin, end);
    }

    inline int length(){return segLen;}

    template<typename iter>
    void build(iter begin, iter end, int root = 0){
        int size = end-begin;
        if(!root){
            int heapLen = pow(2,floor(log2(size*2+2))+1)-1;
            segLen = size;
            storage.resize(heapLen);
            tags = vector<bool>(heapLen, false);
        }
        if(size == 1){
            storage[root] = *begin;
            return;
        }
        build(begin, begin+size/2,left(root));
        build(begin+size/2, end, right(root));
        storage[root] = storage[left(root)] + storage[right(root)];
    }
    type query(int begin, int end, int root=0, int lower=0, int upper=0){
        if(!root) upper = segLen;
        int size=upper-lower;
        if(size==1) return storage[root];
        if(tags[root]) pushDown(root,size);
        if(begin==lower && end==upper) return storage[root];
        if(end<=lower+size/2) return query(begin, end, left(root), lower, lower+size/2);
        if(lower+size/2<=begin) return query(begin,end, right(root), lower+size/2,upper);
        return query(begin, lower+size/2, left(root), lower, lower+size/2) + query(lower+size/2, end, right(root), lower+size/2, upper);
    }
    type update(int begin, int end, type val, int root=0, int lower=0, int upper=0){
        if(!root) upper = segLen;
        int size=upper-lower;
        if(size==1) return storage[root]=val;
        if(tags[root]) pushDown(root,size);
        if(begin==lower && end==upper){
            storage[root]=val;
            tags[root]=true;
            return multiply(val,size);
        }
        if(end<=lower+size/2) return storage[root] = update(begin, end, val, left(root), lower, lower+size/2) + storage[right(root)];
        if(lower+size/2<=begin) return storage[root] = storage[left(root)] + update(begin,end, val, right(root), lower+size/2,upper);
        return storage[root] = update(begin, lower+size/2, val, left(root), lower, lower+size/2) + update(lower+size/2, end, val, right(root), lower+size/2, upper);
    }
};


int main(){
    vector<int> arr(50,1);
    SegTree<int> t(arr.begin(),arr.end());
    t.update(0,50,2);
    cout<<t.query(11,25)<<endl;
    return 0;
}

