#include <bits/stdc++.h>

using namespace std;

template<typename iter>
typename iterator_traits<iter>::value_type&
findN(iter begin, iter end, int n, bool init=true){
    typedef typename iterator_traits<iter>::value_type type;
    int size=end-begin;
    if(init) srand(time(NULL));
    if(size<1) throw std::exception();
    if(size==1) return *begin;
    swap(begin[rand()%size],begin[0]);
    int pivot=0;
    for(int cnt=1;cnt<size;cnt++)
        if(begin[cnt]<begin[0])
            swap(begin[++pivot],begin[cnt]);
    swap(begin[0],begin[pivot]);
    if(n==pivot) return begin[n];
    if(n<pivot) return findN(begin,begin+pivot,n,false);
    return findN(begin+pivot+1,end,n-pivot-1,false);
}

int main(){
    string str="This is to find the smallest N.";
    for(int cnt=0;cnt<str.size();cnt++)
        cout<<findN(str.begin(),str.end(),cnt);
    cout<<endl;
    sort(str.begin(),str.end());
    cout<<str<<endl;
    return 0;
}
