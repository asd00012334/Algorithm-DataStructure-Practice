#include <bits/stdc++.h>

using namespace std;

template<typename type>
void mergeSort(type* begin, type* end){
    if(begin+1>=end) return;
    type* mid = begin+(end-begin)/2;

    /**Divide**/
    mergeSort(begin,mid);
    mergeSort(mid,end);

    /**Merge**/
    type *form = begin;
    type *latt = mid;
    type tempArr[end-begin];
    for(int cnt=0;cnt<sizeof(tempArr);cnt++)
        if(form!=mid && latt!=end)
            if(*form<*latt)
                tempArr[cnt] = *(form++);
            else
                tempArr[cnt] = *(latt++);
        else if(form != mid)
            tempArr[cnt] = *(form++);
        else if(latt != end)
            tempArr[cnt] = *(latt++);
    for(type* cnt=begin; cnt!=end ; ++cnt)
        *cnt = tempArr[cnt-begin];
}


int main(){
    int arr[] = {1, 5, 10, 10, 5, 1};
    mergeSort(arr, arr+sizeof(arr)/sizeof(int));
    for(int cnt=0;cnt<sizeof(arr)/sizeof(int); cnt++)
        cout<< arr[cnt] <<" ";
    cout<<endl;
}
