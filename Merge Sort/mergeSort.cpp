#include <bits/stdc++.h>

using namespace std;

template<typename iter>
void mergeSort(iter begin, iter end){
    int size=end-begin;
    if(size<=1) return;
    iter mid = begin+size/2;

    /**Divide**/
    mergeSort(begin,mid);
    mergeSort(mid,end);

    /**Merge**/
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
        else if(latt != end)
            tempArr[cnt] = *(latt++);
    for(iter cnt=begin; cnt!=end ; ++cnt)
        *cnt = tempArr[cnt-begin];
}


int main(){
    int arr[] = {1, 5, 10, 10, 5, 1};
    mergeSort(arr, arr+sizeof(arr)/sizeof(int));
    for(int cnt=0;cnt<sizeof(arr)/sizeof(int); cnt++)
        cout<< arr[cnt] <<" ";
    cout<<endl;
}
