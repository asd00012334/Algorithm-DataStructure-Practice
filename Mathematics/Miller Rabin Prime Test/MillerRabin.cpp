#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll liarInt[3] = {2,7,61};
ll liarLL[7] = {2,325,9375,28178,450775,9780504,1795265022};

template<typename Int>
inline Int power(Int base, Int expo, Int mod){
    Int out = 1;
    for(;expo;expo>>=1, base=base*base%mod)
        if(expo&1) out=out*base%mod;
    return out;
}

template<typename Int>
bool MillerRabin(Int n){
    if(n<=2) return n==2;
    Int r = 0;
    Int d = n-1;
    for(;!(d&1);++r, d>>=1);
    for(auto liar: liarInt){
        if(liar>=n) continue;
        liar = power(liar%n,d,n);
        if(liar==1) continue;
        bool existN1 = false;
        for(int cnt=r;cnt;--cnt,liar=liar*liar%n)
            if(liar==n-1){
                existN1=true;
                break;
            }
        if(!existN1) return false;
    }
    return true;
}

int main(){
    ll n;
    while(cin>>n){
        if(MillerRabin(n)) printf("Prime\n");
        else printf("Composite\n");
    }
    return 0;
}
