#include <bits/stdc++.h>

using namespace std;

template<typename iter>
void shiftDown(iter begin, iter end, int cur){
    int size = end-begin;
    if(!size) return;
    while(1){
        if(2*cur+2<size){
            if(begin[cur]<begin[2*cur+1] || begin[cur]<begin[2*cur+2])
                if(begin[2*cur+1] < begin[2*cur+2]){
                    swap(begin[cur],begin[2*cur+2]);
                    cur = 2*cur+2;
                }
                else{
                    swap(begin[cur],begin[2*cur+1]);
                    cur = 2*cur+1;
                }
            else break;
        }
        else if(2*cur+1<size){
            if(begin[cur]<begin[2*cur+1]){
                swap(begin[cur],begin[2*cur+1]);
                cur = 2*cur+1;
            }
            else break;
        }
        else break;
    }
}

template<typename iter>
void heapSort(iter begin, iter end){
    int size = end-begin;
    if(!size) return;
    /**Max Heapify**/
    for(int cur=size-1;cur>=0;cur--)
        shiftDown(begin,end,cur);

    /**Deletion and Modification**/
    while(size){
        swap(begin[0],begin[--size]);
        shiftDown(begin,begin+size,0);
    }
}


int main(){
    string input = "This is a Heap Sort.";
    heapSort(input.begin(),input.end());
    for(int cnt=0;cnt<input.size();cnt++)
        cout<<input[cnt];
    cout<<endl;
    return 0;
}
