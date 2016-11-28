#include <bits/stdc++.h>

using namespace std;

template<typename iter>
void iterMerge(iter begin, iter mid, iter end){
    typedef typename iterator_traits<iter>::value_type type;
    int size=0;
    int bound=end-begin;
    iter left=begin;
    iter right=mid;
    type arr[bound];
    while(size<bound){
        if(left>=mid) arr[size++]=*(right++);
        else if(right>=end) arr[size++]=*(left++);
        else{
            if(*left<*right) arr[size++]=*(left++);
            else arr[size++]=*(right++);
        }
    }
    for(int cnt=0;cnt<size;cnt++)
        begin[cnt]=arr[cnt];
}

template<typename iter>
void iterMergeSort(iter begin, iter end){
    int size=end-begin;
    for(int len=1;len<size;len<<=1)
    for(int cnt=0;cnt+len<size;cnt+=2*len)
        iterMerge(begin+cnt,begin+cnt+len,begin+min(cnt+len*2,size));

}

int main(){
    string str="This is an Iterative Merge Sort.";
    iterMergeSort(str.begin(),str.end());
    cout<<str<<endl;
    return 0;
}
