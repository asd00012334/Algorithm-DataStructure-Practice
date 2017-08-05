#include<bits/stdc++.h>
#define ll long long
using namespace std;

/// CodeForces - 617E

#define int ll
int sqtn;
struct Query{
    int l,r;
    int idx;
    int ans;
    Query(){}
    Query(int l, int r, int idx): l(l),r(r),idx(idx){}
    friend bool operator<(Query const& l, Query const& r){
        return l.l/sqtn<r.l/sqtn||
            l.l/sqtn==r.l/sqtn&&l.r<r.r;
    }
    friend bool sameBlock(Query const& l, Query const& r){
        return l.l/sqtn==r.l/sqtn;
    }
};

#define nSize (1<<21)
ll number[nSize];

int transit(Query from, Query to, vector<int> const& a, int k){
    while(1){
        if(from.l>to.l){
            from.ans += number[k^a[--from.l]];
            ++number[a[from.l]];
        } else if(from.r<to.r){
            from.ans += number[k^a[++from.r]];
            ++number[a[from.r]];
        } else if(from.l<to.l){
            --number[a[from.l]];
            from.ans -= number[k^a[from.l++]];
        } else if(from.r>to.r){
            --number[a[from.r]];
            from.ans -= number[k^a[from.r--]];
        } else break;
    }
    return from.ans;
}

int brute(Query q, vector<int> const& a, int k){
    int total=0;
    Query init(q.l,q.l-1,0);
    init.ans=0;
    for(int cnt=0;cnt<nSize;cnt++) number[cnt]=0;
    return transit(init,q,a,k);
}
#undef int

int main(){
    #define int ll
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> a(n+1,0);
    for(int cnt=1;cnt<=n;cnt++){
        scanf("%I64d",&a[cnt]);
        a[cnt] ^= a[cnt-1];
    }
    vector<Query> q(m);
    int maxi=0, mini=INT_MAX;
    for(int cnt=0;cnt<m;cnt++){
        scanf("%I64d%I64d",&q[cnt].l,&q[cnt].r);
        q[cnt].idx = cnt;
        --q[cnt].l;
        maxi = max(maxi,q[cnt].l);
        mini = min(mini,q[cnt].l);
    }
    sqtn=sqrt(maxi-mini);
    sort(q.begin(),q.end());
    q[0].ans = brute(q[0],a,k);
    for(int cnt=1;cnt<q.size();cnt++){
        if(sameBlock(q[cnt-1],q[cnt]))
            q[cnt].ans = transit(q[cnt-1],q[cnt],a,k);
        else q[cnt].ans = brute(q[cnt],a,k);
    }
    vector<int> ans(m,0);
    for(int cnt=0;cnt<q.size();cnt++)
        ans[q[cnt].idx] = q[cnt].ans;
    for(int cnt=0;cnt<ans.size();cnt++)
        printf("%I64d\n",ans[cnt]);
    return 0;
    #undef int
}
