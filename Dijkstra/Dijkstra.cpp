#include<bits/stdc++.h>
#define MAX(x) ((x)1<<(sizeof(x)*8-1)-1)
using namespace std;

void Dijkstra(
	vector<vector<pair<int,int> > > &adjList, // cap, dest
	vector<int>& stp, // shortest path distance from s
	vector<int>& intro,
	int s
){
	int n = adjList.size();
	stp = vector<int>(n,INT_MAX);
	stp[s] = 0;
	vector<bool> tra(n,false);
	intro = vector<int>(n,-1);
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pQ;
	pQ.push(pair<int,int>(0,s));
	while(pQ.size()){
		pair<int,int> cur = pQ.top();
		pQ.pop();
		for(int cnt=0;cnt<adjList[cur.second].size();cnt++){
			auto nxt = adjList[cur.second][cnt];
			if(tra[nxt.second]) continue;
			nxt.first+=stp[cur.second];
			pQ.push(nxt);
			if(nxt.first<stp[nxt.second]){
				intro[nxt.second] = cur.second;
				stp[nxt.second] = nxt.first;
			}
		}
		tra[cur.second] = true;
	}
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
	Dijkstra(adjList,stp,intro,0);
	if(stp[n-1]==INT_MAX){
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
