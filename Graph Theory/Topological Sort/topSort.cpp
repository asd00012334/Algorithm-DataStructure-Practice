#include<bits/stdc++.h>

using namespace std;

void topSort(
    vector<vector<int> > const& adjList,
    vector<int> &result
){
    int n = adjList.size();
    result.clear();
    vector<bool> tra(n,false);
    for(int s=0;s<n;s++){
        if(tra[s]) continue;
        vector<int> stk(1,s);
        tra[s] = true;
        while(stk.size()){
            int cur = stk.back();
            bool endPt = true;
            for(int cnt=0;cnt<adjList[cur].size();cnt++){
                int nxt = adjList[cur][cnt];
                if(tra[nxt]) continue;
                endPt = false;
                stk.push_back(nxt);
                tra[nxt] = true;
            }
            if(endPt){
                stk.pop_back();
                result.push_back(cur);
            }
        }
    }
    reverse(result.begin(),result.end());
}

int main(){
    while(1){
        int n,m;
        cin>>n>>m;
        if(!n && !m) break;
        vector<vector<int> > adjList(n);
        while(m--){
            int a,b;
            scanf("%d%d",&a,&b); a--; b--;
            adjList[a].push_back(b);
        }
        vector<int> result;
        topSort(adjList,result);
        for(int cnt=0;cnt<n;cnt++){
            if(cnt) printf(" ");
            printf("%d",result[cnt]+1);
        }
        printf("\n");
    }

    return 0;
}
