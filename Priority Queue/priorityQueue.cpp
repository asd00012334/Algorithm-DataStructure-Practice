#include <bits/stdc++.h>

using namespace std;

template<typename type>
class priorityQueue{
private:
    vector<type> storage;
public:
    size_t size(){return storage.size();}
    void push(type ins){
        int insIndex;
        insIndex = storage.size();
        storage.push_back(ins);
        for(;storage[insIndex]<storage[(insIndex-1)/2]&&insIndex;insIndex=(insIndex-1)/2)
            std::swap(storage[(insIndex-1)/2],storage[insIndex]);
    }
    type const& top(){return storage.at(0);}
    void pop(){
        if(storage.empty()) return;
        std::swap(storage.front(),storage.back());
        storage.pop_back();
        int curIndex = 0;
        while(1){
            if(2*curIndex+1<storage.size() && 2*curIndex+2<storage.size()){
                if(storage[2*curIndex+1]<storage[curIndex] || storage[2*curIndex+2]<storage[curIndex])
                    if(storage[2*curIndex+1]<storage[2*curIndex+2]){
                        std::swap(storage[curIndex],storage[2*curIndex+1]);
                        curIndex = 2*curIndex+1;
                    }
                    else{
                        std::swap(storage[curIndex],storage[2*curIndex+2]);
                        curIndex = 2*curIndex+2;
                    }
                    else break;
            }
            else if(2*curIndex+1<storage.size() && storage[2*curIndex+1]<storage[curIndex]){
                std::swap(storage[curIndex],storage[2*curIndex+1]);
                curIndex = 2*curIndex+1;
            }
            else break;
        }
    }
    bool empty(){return storage.empty();}
    void swap(priorityQueue<type>& right){storage.swap(right.storage);}
};

int main(){
    string input = "This is a Priority Queue.";
    priorityQueue<char> pQ;
    for(int cnt=0;cnt<input.size();cnt++)
        pQ.push(input[cnt]);

    while(pQ.size()){
        cout<<pQ.top();
        pQ.pop();
    }
    cout<<endl;
    return 0;
}
