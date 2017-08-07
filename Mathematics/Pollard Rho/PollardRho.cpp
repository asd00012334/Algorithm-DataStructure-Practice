#include<bits/stdc++.h>
#define ll long long
using namespace std;

int liarInt[3] = {2,7,61};
ll liarLL[7] = {2,325,9375,28178,450775,9780504,1795265022};

inline int mul(int const& a, int const& b, int const& mod){return (ll)a*b%mod;}
inline ll mul(ll a, ll b, ll mod){
    ll out = 0;
    a%=mod; b%=mod;
    for(;b;b>>=1){
        if(b&1) if((out+=a)>=mod) out-=mod;
        if((a<<=1)>= mod) a-=mod;
    }
    return out;
}


template<typename Int>
inline Int power(Int base, Int expo, Int mod){
    Int out = 1;
    for(;expo;expo>>=1, base=mul(base,base,mod) )
        if(expo&1) out=mul(out,base,mod);
    return out;
}

template<typename Int>
bool MillerRabin(Int n){
    if(n<=2) return n==2;
    Int r = 0;
    Int d = n-1;
    for(;!(d&1);++r, d>>=1);
    for(auto liar: liarLL){
        if(liar>=n) continue;
        liar = power(liar%n,d,n);
        if(liar==1) continue;
        bool existN1 = false;
        for(int cnt=r;cnt;--cnt,liar=mul(liar,liar,n))
            if(liar==n-1){
                existN1=true;
                break;
            }
        if(!existN1) return false;
    }
    return true;
}

template<typename Int>
Int PollardRho(Int n){
    #define nxt(x) ((mul(x,x,n)+c)%n)
    Int c = rand()%n;
    Int candidate = rand()%n;
    Int pivot=nxt(candidate);
    while(candidate!=pivot){
        Int factor = __gcd(n,abs(candidate-pivot));
        if(1<factor&&factor<n) return factor;
        candidate = nxt(candidate);
        pivot = nxt(nxt(pivot));
    }
    return 0;
    #undef nxt
}

template<typename Int>
void factorize(Int n, set<Int>& pfactor){
    vector<Int> stk(1,n);
    while(stk.size()){
        Int cur=stk.back(); stk.pop_back();
        if(MillerRabin(cur)){
            pfactor.insert(cur);
            continue;
        }
        Int factor;
        do factor=PollardRho(cur); while(!factor);
        stk.push_back(factor); stk.push_back(cur/factor);
    }
}

int main(){
    ll n;
    srand(time(NULL));
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        if(MillerRabin(n)) cout<<"Prime\n";
        else{
            set<ll> pfactor;
            factorize(n,pfactor);
            cout<<*pfactor.begin()<<"\n";
        }
    }
    return 0;
}
