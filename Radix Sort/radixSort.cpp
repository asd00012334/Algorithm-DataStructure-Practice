#include <bits/stdc++.h>

using namespace std;

template<typename iter>
void radixSort(iter begin, iter end){
    typedef typename iterator_traits<iter>::value_type type;
    int size = end-begin;
    if(size<=0) return;
    int bitNum = sizeof(type)*8;
    for(int bit=0;bit<bitNum-1;bit++){
        vector<type> radix[2];
        for(int cnt=0;cnt<size;cnt++)
            if(begin[cnt]&(1<<bit))
                radix[1].push_back(begin[cnt]);
            else
                radix[0].push_back(begin[cnt]);
        for(int cnt=0;cnt<radix[0].size();cnt++)
            begin[cnt]=radix[0][cnt];
        for(int cnt=0;cnt<radix[1].size();cnt++)
            begin[cnt+radix[0].size()]=radix[1][cnt];
    }
    vector<type> pos[2];
    for(int cnt=0;cnt<size;cnt++)
        if(begin[cnt]<0)
            pos[0].push_back(begin[cnt]);
        else
            pos[1].push_back(begin[cnt]);
    for(int cnt=pos[0].size()-1;cnt>=0;cnt--)
        begin[cnt] = pos[0][cnt];
    for(int cnt=0;cnt<pos[1].size();cnt++)
        begin[cnt+pos[0].size()] = pos[1][cnt];
}


int main(){
    string input = "This is a Radix Sort.";
    radixSort(input.begin(),input.end());
    for(int cnt=0;cnt<input.size();cnt++)
        cout<<input[cnt];
    cout<<endl;
    return 0;
}
