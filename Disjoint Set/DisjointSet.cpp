#include <bits/stdc++.h>

using namespace std;

template<typename type>
class DisjointSet{
    size_t groups;
    vector<int> storage;
    vector<int> card;
    unordered_map<type,int> info;
    int findSetKernel(int idx){
        if(storage[idx]==idx) return idx;
        return storage[idx]=findSetKernel(storage[idx]);
    }
public:
    DisjointSet():groups(0){}

    template<typename iter>
    DisjointSet(iter begin, iter end){
        makeSet(begin, end);
    }

    template<typename iter>
    void makeSet(iter begin, iter end){
        size_t sizeBound=end-begin;
        storage.resize(sizeBound);
        card.resize(sizeBound);
        info.clear();
        groups=0;
        for(int cnt=0;cnt<sizeBound;cnt++){
            if(info.count(begin[cnt]))continue;
            storage[groups]=groups;
            card[groups]=1;
            info[begin[cnt]]=groups;
            groups++;
        }
        storage.resize(groups);
        card.resize(groups);
    }

    int findSet(type elem){
        if(!info.count(elem)) return -1;
        int idx=info[elem];
        return findSetKernel(idx);
    }

    void unionSet(type l, type r){
        int lHead=findSet(l);
        int rHead=findSet(r);
        if(lHead==rHead) return;
        --groups;
        storage[rHead]=lHead;
        card[lHead]+=card[rHead];
        card[rHead]=0;
    }

    bool equal(type l, type r){return findSet(l)==findSet(r);}

    size_t cardinality(type elem){return card[findSet(elem)];}

    inline size_t size(){return groups;}

    void clear(){
        groups=0;
        storage.clear();
        card.clear();
        info.clear();
    }
};

int main(){
    vector<int> arr(10);
    for(int cnt=0;cnt<10;cnt++)
        arr[cnt]=cnt;
    arr[5]=4;
    DisjointSet<int> dst(arr.begin(),arr.end());
    cout<<dst.size()<<endl;
    dst.unionSet(2,3);
    dst.unionSet(3,4);
    if(dst.equal(2,4))
        cout<<"Equal"<<endl;
    cout<<dst.size()<<endl;
    cout<<dst.cardinality(2)<<endl;
    cout<<dst.findSet(2)<<endl;
    return 0;
}
