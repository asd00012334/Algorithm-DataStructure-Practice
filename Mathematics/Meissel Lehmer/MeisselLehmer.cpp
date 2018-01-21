#include<bits/stdc++.h>
#define ll long long

using namespace std;

#define SIEVE_SIZE 1000000

vector<int> prime;
int sieve[SIEVE_SIZE];

void init(){
    prime.clear();
    memset(sieve,0,sizeof(sieve));
    for(int i=2;i<SIEVE_SIZE;++i){
        if(!sieve[i]) prime.push_back(i);
        for(int j=0;i*prime[j]<SIEVE_SIZE;++j){
            sieve[i*prime[j]] = 1;
            if(i%prime[j]==0) break;
        }
    }
    for(int i=2;i<SIEVE_SIZE;++i)
        sieve[i] = !sieve[i] + sieve[i-1];
}

ll p2(ll m, int n);
ll phi(ll m, int n);
ll pi(ll m);

ll p2(ll m, int n){
    int sqtm = sqrt(m);
    ll out = 0;
    for(int i=n;prime[i]<=sqtm;++i)
        out+=pi(m/prime[i])-pi(prime[i])+1;
    return out;
}

ll phi(ll m, int n){
    if(n==0 || m==0) return m;
    if(m<=n) return 1;
    if((ll)prime[n-1]*prime[n-1]>=m)
        return pi(m)-n+1;
    return phi(m,n-1)-phi(m/prime[n-1],n-1);
}

ll pi(ll m){
    if(m<SIEVE_SIZE) return sieve[m];
    int n = ceil(cbrt(m));
    return phi(m,n)+n-1-p2(m,n);
}

int main(){
    init();
    ll m;
    while(cin>>m)
        cout<<pi(m)<<"\n";
}
