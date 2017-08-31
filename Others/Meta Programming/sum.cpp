#include<bits/stdc++.h>

using namespace std;

/// Sum out const-size non-empty array
/// i.e. sum<5, int>::get(arr) = arr[0]+arr[1]+...+arr[4]
template<int size, typename type>
struct sum{
    static inline type get(type const arr[]){
        return *arr+sum<size-1,type>::get(arr+1);
    }
};

template<typename type>
struct sum<0,type>{
    static inline type get(type const arr[]){
        return type();
    }
};

int main(){
    return 0;
}
