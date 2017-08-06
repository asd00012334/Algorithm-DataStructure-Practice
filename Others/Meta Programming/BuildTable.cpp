#include<bits/stdc++.h>

using namespace std;

/// C<n,k>::val
template<int n, int k> struct C{ static const int val = C<n-1,k>::val+C<n-1,k-1>::val;};
template<int n> struct C<n,0>{ static const int val=1;};
template<int k> struct C<k,k>{ static const int val=1;};

/// Table<length,n,0>::arr[k]
template<int length, int n, int k> struct Table: Table<length, n, k-1>{ static const int dummy;};
template<int length, int n> struct Table<length,n,0>{ static int const dummy; static int arr[length];};
template<int length, int n, int k> const int Table<length,n,k>::dummy = Table<length,n,0>::arr[k] = C<n,k>::val+Table<length,n,k-1>::dummy*0;
template<int length, int n> int Table<length,n,0>::arr[length];
template<int length, int n> const int Table<length,n,0>::dummy = Table<length,n,0>::arr[0] = C<n,0>::val;
template struct Table<5,5,5>;

int main(){
    cout<<C<5,3>::val<<"\n";
    cout<<Table<5,5,0>::arr[3]<<"\n";
}
