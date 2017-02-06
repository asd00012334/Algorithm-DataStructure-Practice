#include <bits/stdc++.h>

using namespace std;

template<typename iter>
void thrdMergeSort(iter begin, iter end){
    int size=end-begin;
    if(size<=1) return;
    iter mid=begin+size/2;
    thread rThread;
    try{
        rThread=thread(thrdMergeSort<iter>,mid,end);
    }catch(exception){
        thrdMergeSort(mid,end);
    }
    thrdMergeSort(begin,mid);
    rThread.join();
    iter form = begin;
    iter latt = mid;
    typename iterator_traits<iter>::value_type tempArr[size];
    for(int cnt=0;cnt<size;cnt++)
        if(form!=mid && latt!=end)
            if(*form<*latt)
                tempArr[cnt] = *(form++);
            else
                tempArr[cnt] = *(latt++);
        else if(form != mid)
            tempArr[cnt] = *(form++);
        else tempArr[cnt] = *(latt++);
    for(iter cnt=begin; cnt!=end ; ++cnt)
        *cnt = tempArr[cnt-begin];
}



int main(){
    string str="This is a Multi-Threading Merge Sort";
    thrdMergeSort(str.begin(),str.end());
    cout<<str<<endl;
    return 0;
}
