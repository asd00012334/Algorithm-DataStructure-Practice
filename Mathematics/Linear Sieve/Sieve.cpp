#include<bits/stdc++.h>
#define ll long long
#define MAX_SIZE (1<<25)
using namespace std;
/// Yet to be tested

bool sieve[MAX_SIZE]={};
vector<int> prime;
void build(){
    sieve[0]=true; sieve[1]=true;
    for(int i=2;i<MAX_SIZE;++i){
        if(!sieve[i]) prime.push_back(i);
        for(int j=0;j<prime.size() && (ll)i*prime[j]<MAX_SIZE;++j){
            sieve[(ll)i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
}

bool isPrime(ll n){
    if(n<MAX_SIZE) return !sieve[n];
    ll sqtn = sqrt(n);
    for(ll cnt=0;cnt<prime.size()&&prime[cnt]<=sqtn;++cnt)
        if(n%prime[cnt]==0) return false;
    return true;
}

int main(){
    ll n;
    build();
    while(cin>>n){
        if(isPrime(n)) printf("質數\n");
        else printf("非質數\n");
    }
}
