#include<bits/stdc++.h>

using namespace std;

template<typename iter>
void fwht(iter begin, iter end){
    typedef typename iterator_traits<iter>::value_type type;
    int size = end-begin;
    type sqt2 = sqrt(2);
    for(int h=1;h<size;h<<=1){
        for(int i=0;i<size;i+=(h<<1))
        for(int j=i;j<i+h;++j){
            type x = begin[j], y = begin[j+h];
            begin[j] = (x + y)/sqt2;
            begin[j+h] = (x - y)/sqt2;
        }
    }
}

int main(){
    vector<double> arr(16,0);
    arr.back() = 1;
    fwht(arr.begin(),arr.end());
    for(int i=0;i<arr.size();++i){
        cout<< arr[i]<<" ";
    }
    puts("");

}
