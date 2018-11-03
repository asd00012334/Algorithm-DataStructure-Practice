#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,m;
    while(cin>>n>>m){
        if(!n && !m) break;
        vector<vector<int> > adjList(n);
        for(int i=0;i<m;++i){
            int u,v;scanf("%d%d",&u,&v);
            --u, --v;
            adjList[u].push_back(v);
        }

        /// Tarjan's SCC
        int t = 0;
        vector<int> vis(n,0), stk, root(n);
        vector<int> onChain(n,0), low(n), in(n);
        function<int(int)> dfs = [&](int u){
            low[u] = in[u] = t++;
            onChain[u] = 1;
            stk.push_back(u);
            int sccN = 0;
            for(int i=0;i<adjList[u].size();++i){
                int v = adjList[u][i];
                if(!vis[v]){
                    vis[v] = 1;
                    sccN += dfs(v);
                }
                if(onChain[v]){
                    /// backward edge: update time flag of scc
                    low[u] = min(low[v],low[u]);
                }
            }
            if(in[u]==low[u]){
                /// u is the root of scc
                ++sccN;
                int v=-1;
                while(u!=v){
                    v = stk.back();
                    stk.pop_back();
                    root[v] = u;
                    onChain[v] = 0;
                }
            }
            return sccN;
        };
        int sccN = 0;
        for(int i=0;i<n;++i){
            if(vis[i]) continue;
            vis[i] = 1;
            sccN += dfs(i);
        }

        if(sccN==1) puts("Yes");
        else puts("No");
    }
    return 0;
}
