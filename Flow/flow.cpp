#include<bits/stdc++.h>
#define MAX(x) ((x)(1<<(sizeof(x)*8-1))-1)
using namespace std;

int EdmondKarp(
	vector<vector<int> >& adjList,
	vector<vector<int> >& cap,
	int s, int t
){
	int f=0;
	int n = adjList.size();
	while(1){
		bool flag = false;
		queue<int> que;
		vector<bool> tra(n,false);
		vector<int> intro(n,-1);
		que.push(s);
		tra[s] = true;
		while(que.size()){
			int cur = que.front();
			que.pop();
			if(cur == t){
				flag = true;
				break;
			}
			for(int cnt=0;cnt<adjList[cur].size();cnt++){
				int nxt = adjList[cur][cnt];
				if(tra[nxt] || cap[cur][nxt]<=0) continue;
				tra[nxt] = true;
				que.push(nxt);
				intro[nxt] = cur;
			}
		}
		if(!flag) break;
		int bottleNeck=MAX(int);
		for(int p=t;intro[p]!=-1;p = intro[p])
			bottleNeck = min(bottleNeck, cap[intro[p]][p]);
		for(int p=t;intro[p]!=-1;p = intro[p]){
			cap[intro[p]][p]-=bottleNeck;
			cap[p][intro[p]]+=bottleNeck;
		}
		f+=bottleNeck;
	}
	return f;
}

int Dinic(
	vector<vector<int> >& adjList,
	vector<vector<int> >& cap,
	int s, int t
){
	int f=0;
	int n=adjList.size();
	while(1){
		vector<int> level(n);
		vector<bool> tra(n,false);
		queue<int> que;
		que.push(s);
		level[s]=0;
		tra[s] = true;
		bool noLevel = true;
		while(que.size()){
			int cur = que.front();
			que.pop();
			if(cur==t) noLevel = false;
			for(int cnt=0;cnt<adjList[cur].size();cnt++){
				int nxt = adjList[cur][cnt];
				if(tra[nxt] || cap[cur][nxt]<=0) continue;
				level[nxt] = level[cur]+1;
				que.push(nxt);
				tra[nxt] = true;
			}
		}
		if(noLevel) break;
		while(1){
			tra = vector<bool>(n,false);
			bool augPossible = false;
			vector<int> stk(1,s);
			vector<int> intro(n,-1);
			while(stk.size()){
				int cur = stk.back();
				stk.pop_back();
				if(cur == t){
					augPossible = true;
					break;
				}
				for(int cnt=0;cnt<adjList[cur].size();cnt++){
					int nxt = adjList[cur][cnt];
					if(tra[nxt] || cap[cur][nxt]<=0 || level[cur]>=level[nxt]) continue;
					intro[nxt] = cur;
					stk.push_back(nxt);
					tra[nxt] = true;
				}
			}
			if(!augPossible) break;
			int bottleNeck=MAX(int);
			for(int p=t;intro[p]!=-1;p = intro[p])
				bottleNeck = min(bottleNeck, cap[intro[p]][p]);
			for(int p=t;intro[p]!=-1;p = intro[p]){
				cap[intro[p]][p]-=bottleNeck;
				cap[p][intro[p]]+=bottleNeck;
			}
			f+=bottleNeck;
		}
	}
	return f;
}

int main(){
	int t;
	cin>>t;
	for(int tm=1;tm<=t;tm++){
		int n,m;
		cin>>n>>m;
		vector<vector<int> > cap(n,vector<int>(n,0));
		vector<vector<int> > adjList(n);
		for(int cnt=0;cnt<m;cnt++){
			int a,b,c;
			cin>>a>>b>>c;
			a--; b--;
			adjList[a].push_back(b);
			adjList[b].push_back(a);
			cap[a][b] += c;
		}
		cout<<"Case "<<tm<<": "<<EdmondKarp(adjList, cap, 0, n-1)<<"\n";
		
	}
}
