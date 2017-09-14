#include<bits/stdc++.h>

using namespace std;

bool cycle(vector<vector<int> > const& adjList){
    int n = adjList.size();
    vector<bool> vis(n,0);
    vector<bool> drop(n,0);
    vector<int> stk;
    for(int s=0;s<n;++s){
        if(vis[s]) continue;
        stk.push_back(s);
        while(stk.size()){
            int cur = stk.back();
            if(vis[cur]){
                drop[cur] = true;
                stk.pop_back();
                continue;
            }
            vis[cur] = true;
            for(int i=0;i<adjList[cur].size();++i){
                int nxt = adjList[cur][i];
                if(drop[nxt]) continue;
                if(vis[nxt]) return true;
                stk.push_back(nxt);
            }

        }
    }
    return false;
}

int main(){
    while(1){
        int n,m;
        cin>>n>>m;
        if(!n && !m) break;
        vector<vector<int> > adjList(n);
        while(m--){
            int a,b;
            scanf("%d%d",&a,&b); a; b;
            adjList[a].push_back(b);
        }
        cout<<cycle(adjList)<<"\n";
    }

    return 0;
}
