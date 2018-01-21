#include<bits/stdc++.h>
#define ll long long
using namespace std;

int pow_m(ll a, int b, int mod){
    int out = 1;
    for(int stp=1;b;stp<<=1,a=a*a%mod)
        if(b&stp) out=out*a%mod, b-=stp;
    return out;
}

/// Shank
int dLog(int a, ll b, int p){
    unordered_map<int,int> vis;
    int inva = pow_m(a,p-2,p);
    int m = ceil(sqrt(p-1));
    int gstep = pow_m(a,m,p);
    for(int i=0;i<m;++i,b=b*inva%p) vis[b] = i;
    ll g=1;
    for(int i=0;i<m;++i,g=g*gstep%p)
        if(vis.count(g)) return (ll)m*i+vis[g];
    return -1;
}

int main(){
    int p,b,n;
    while(~scanf("%d%d%d",&p,&b,&n)){
        int result = dLog(b,n,p);
        if(result==-1) puts("no solution");
        else printf("%d\n",result);
    }

    return 0;
}
