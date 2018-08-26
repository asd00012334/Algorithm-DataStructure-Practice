#include<bits/stdc++.h>

using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int n, m; cin>>n>>m;
        vector<vector<pair<int,int> > > adjList(n);
        for(int i=0;i<n-1;++i){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            --u, --v;
            adjList[u].push_back({v,w});
            adjList[v].push_back({u,w});
        }
        vector<vector<int> > parent(n);

        struct Node{
            int in, out, depth;
        };

        vector<int> vis(n,0);
        vector<Node> arr(n);
        arr[0].depth = 0;
        int t = 0;
        function<void(int,int)> dfs = [&](int u, int depth){
            arr[u].in = t++;
            arr[u].depth = depth;
            for(int i=0;i<adjList[u].size();++i){
                int nxt = adjList[u][i].first;
                if(vis[nxt]) continue;
                vis[nxt] = 1;
                for(int p=u, i=0;;++i){
                    parent[nxt].push_back(p);
                    if(i>=parent[p].size()) break;
                    p = parent[p][i];
                }
                dfs(nxt, depth+adjList[u][i].second);
            }
            arr[u].out = t++;
        };
        vis[0] = 1;
        dfs(0,0);

        auto isUpper = [&](int u, int v){
            return arr[u].in<arr[v].in && arr[v].out<arr[u].out;
        };
        function<int(int,int)> lca = [&](int u, int v){
            if(u==v) return u;
            if(isUpper(u,v)) return u;
            if(isUpper(v,u)) return v;
            if(isUpper(parent[u][0],v))
                return parent[u][0];
            int i;
            for(i=1;i<parent[u].size();++i){
                int jump = parent[u][i];
                if(isUpper(jump, v)) break;
            }
            return lca(parent[u][i-1],v);
        };
        function<int(int,int)> dist = [&](int u, int v){
            if(u==v) return 0;
            if(isUpper(u,v)) return arr[v].depth-arr[u].depth;
            if(isUpper(v,u)) return arr[u].depth-arr[v].depth;


            return arr[u].depth+arr[v].depth-arr[lca(u,v)].depth;
        };

        while(m--){
            int u, v;
            scanf("%d%d",&u,&v);
            --u, --v;
            cout<<dist(u,v)<<"\n";
        }
    }

    return 0;
}
