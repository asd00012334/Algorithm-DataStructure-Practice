#include<bits/stdc++.h>
using namespace std;

/// Sqrt<n,i>
template<int num, int denom, int i> struct Sqrt{ static const double val;};
template<int num, int denom> struct Sqrt<num,denom,0>{ static const double val;};
template<int num, int denom, int i> const double Sqrt<num,denom,i>::val = Sqrt<num,denom,i-1>::val-(Sqrt<num,denom,i-1>::val*Sqrt<num,denom,i-1>::val-Sqrt<num,denom,0>::val)/(2*Sqrt<num,denom,i-1>::val);
template<int num, int denom> const double Sqrt<num,denom,0>::val = (double)num/denom;

int main(){
    cout<<Sqrt<2,1,30>::val<<"\n";
}
