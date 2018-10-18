#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,m;
    while(cin>>n>>m){
        if(n==0 && m==0) break;
        vector<vector<int> > adjList(n);
        for(int i=0;i<m;++i){
            int u,v; scanf("%d%d",&u,&v);
            adjList[--u].push_back(--v);
        }

        /// Topological sort with dfs
        vector<int> stk, vis(n,0);
        function<void(int)> dfs = [&](int u){
            for(int i=0;i<adjList[u].size();++i){
                int v = adjList[u][i];
                if(vis[v]) continue;
                vis[v] = 1;
                dfs(v);
            }
            stk.push_back(u);
        };
        for(int i=0;i<n;++i){
            if(vis[i]) continue;
            vis[i] = 1;
            dfs(i);
        }
        reverse(stk.begin(),stk.end());

        for(int i=0;i<stk.size();++i){
            if(i) printf(" ");
            printf("%d",stk[i]+1);
        }
        puts("");
    }



}
