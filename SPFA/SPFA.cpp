#include<bits/stdc++.h>
#define MAX(x) ((x)(1<<(sizeof(x)*8-1))-1)

using namespace std;

bool SPFA(
	vector<vector<pair<int,int> > > &adjList, // cap, dest
	vector<int>& stp, // shortest path distance from s
	vector<int>& intro,
	int s
){
    int n = adjList.size();
    vector<int> tra(n,false);
    vector<int> counter(n,0);
    queue<int> que;
    stp = vector<int>(n,MAX(int));
    intro = vector<int>(n,-1);
    que.push(s); stp[s] = 0; tra[s] = true; counter[s]++;
    while(que.size()){
        int cur = que.front();
        tra[cur] = false;
        que.pop();
        for(int cnt=0;cnt<adjList[cur].size();cnt++){
            pair<int,int> nxt = adjList[cur][cnt];
            if(stp[cur]+nxt.first>=stp[nxt.second]) continue;
            stp[nxt.second] = stp[cur]+nxt.first;
            intro[nxt.second] = cur;
            if(tra[nxt.second]) continue;
            tra[nxt.second] = true;
            que.push(nxt.second);
            if(++counter[nxt.second]>=n)
                return false;
        }
    }
    return true;
}

int main(){
	int n,m;
	cin>>n>>m;
	vector<vector<pair<int,int> > > adjList(n);
	for(int cnt=0;cnt<m;cnt++){
		int a,b,c;
		cin>>a>>b>>c; a--; b--;
		adjList[a].push_back(pair<int,int>(c,b));
		adjList[b].push_back(pair<int,int>(c,a));
	}
	vector<int> stp, intro;
	SPFA(adjList,stp,intro,0);
	if(stp[n-1]==MAX(int)){
		printf("-1\n");
		return 0;
	}
	vector<int> stk;
	for(int p=n-1;p!=-1;p=intro[p]) stk.push_back(p);
	for(;stk.size();stk.pop_back()){
		cout<<stk.back()+1;
		if(stk.size()>1) printf(" ");
	}
	cout<<"\n";
}
