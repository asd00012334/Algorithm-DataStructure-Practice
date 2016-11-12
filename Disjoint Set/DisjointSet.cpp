#include <bits/stdc++.h>

using namespace std;

template<typename type>
class DisjointSet{
    size_t groups;
    vector<int> head;
    vector<int> card;
    unordered_map<type, int> info;
public:

    inline int find(type const& elem){
        if(!info.count(elem)) return EOF;
        return info[elem];
    }

    template<typename iter>
    DisjointSet(iter begin, iter end){
        makeSet(begin,end);
    }

    DisjointSet():groups(0){}

    template<typename iter>
    void makeSet(iter begin, iter end){
        groups=end-begin;
        if(groups<0) throw exception();
        head.resize(groups);
        card.resize(groups);
        info.clear();
        int top=-1;
        for(int cnt=0;cnt<groups;cnt++){
            if(info.count(begin[cnt])) continue;
            top++;
            head[top]=top;
            card[top]=1;
            info[begin[cnt]]=top;
        }
        groups=top+1;
        head.resize(groups);
        card.resize(groups);
    }

    inline bool equal(type const& left, type const& right){
        if(find(left)==EOF||find(right)==EOF) return false;
        return head[find(left)]==head[find(right)];
    }

    inline size_t size(){return groups;}

    inline void clear(){
        groups=0;
        head.clear();
        card.clear();
        info.clear();
    }

    void unionSet(type const& left, type const& right){
        int leftIdx=find(left);
        int rightIdx=find(right);
        if(leftIdx==EOF||rightIdx==EOF) return;
        if(leftIdx==rightIdx) return;
        int newCard=card[leftIdx]+card[rightIdx];
        for(int cnt=0;cnt<groups;cnt++){
            if(head[cnt]==head[leftIdx]||head[cnt]==head[rightIdx]){
                card[cnt]=newCard;
                head[cnt]=head[leftIdx];
            }
        }
        groups--;
    }

    inline size_t cardinality(type const& elem){
        if(!info.count(elem)) return 0;
        return card[find(elem)];
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
    cout<<dst.find(2)<<endl;
    return 0;
}
