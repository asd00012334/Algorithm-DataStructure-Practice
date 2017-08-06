#include<bits/stdc++.h>
#define TableSize 800
using namespace std;

/// C<n,k>::val
template<int n, int k> struct C{ static const int val;};
template<int n> struct C<n,0>{ static const int val;};
template<int n, int k> const int C<n,k>::val = C<n,k-1>::val*(n-k+1)/k;
template<int n> const int C<n,0>::val=1;

/// Table<n,0>::arr[k]
template<int n, int k> struct Table: Table<n, k-1>{ static const int dummy;};
template<int n> struct Table<n,0>{ static int const dummy; static int arr[n];};
template<int n, int k> const int Table<n,k>::dummy = Table<n,0>::arr[k] = C<n,k>::val+Table<n,k-1>::dummy*0;
template<int n> int Table<n,0>::arr[n];
template<int n> const int Table<n,0>::dummy = Table<n,0>::arr[0] = C<n,0>::val;
template struct Table<TableSize,TableSize>;

int main(){
    cout<<C<TableSize,3>::val<<"\n";
    cout<<Table<TableSize,TableSize>::arr[3]<<"\n";
}
