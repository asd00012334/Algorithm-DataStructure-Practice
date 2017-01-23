#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include "PriorityQueue.hpp"
#include "DisjointSet.hpp"
#define INF (1<<(sizeof(int)*8-1)-1)
using namespace std;

struct Edge{
    /// "from" is an optional member
    /// When not used, -1 is assigned.
    int from;
    int to;
    int dist;
    Edge(int to, int dist, int from=-1):
        to(to), dist(dist), from(from){}
    Edge(){}
    friend bool operator<(Edge const& l, Edge const& r){
        return l.dist<r.dist||
            l.dist==r.dist&&l.to<r.to;
    }
};

/// Kruskal Algorithm
/// Use Disjoint Set to do cycle detection
/// Outline:-----------------------------------------------------------------
/// First, sort the edges with respect to their weight
/// Then add them one by one from smallest weight to greatest weight.
/// In the same time, add the terminal point of the edges into disjoint set
/// and detect if there's a pair of node already in the same set before union
/// If so, it means the new edge forms a cycle, so we just abandon the edge
/// Otherwise, it is a part of the Minimum Spanning Tree.
void spanning(Vector<Vector<Edge> >&adjList){
    int n=adjList.size();
    Vector<Edge> edgList;
    for(int from=0;from<n;from++)
    for(int cnt=0;cnt<adjList[from].size();cnt++)
        edgList.push_back(Edge(adjList[from][cnt].to,adjList[from][cnt].dist,from));
    heapSort(edgList.begin(),edgList.end());
    DisjointSet ds(n);
    bool space=false;
    int spanSize=0;
    for(int cnt=0;cnt<edgList.size();cnt++){
        int from=edgList[cnt].from;
        int to=edgList[cnt].to;
        if(!ds.equal(from,to)){
            edgList[spanSize++]=edgList[cnt];
            ds.unionSet(from,to);
        }
    }
    if(spanSize<n-1){
        printf("No spanning tree\n");
        return;
    }
    for(int cnt=0;cnt<spanSize;cnt++){
        if(cnt) printf(" ");
        printf("(%d, %d);",edgList[cnt].from,edgList[cnt].to);
    }
    printf("\n");
}

/**
/// Prim Algorithm
/// Use Priority Queue to optimize
/// Outline:-----------------------------------------------------------------
/// First, choose 0 as a starting point in the MST
/// Push in each adjacent edge into the Priority Queue
/// Take out the nearest point in the Priority Queue,
/// if it has not been traversed,
/// join the point into the MST and mark it as traversed;
/// Otherwise, just ignore the point
/// Loop until every walkable point has been traversed.
/// Finally we'll get an MST
void spanning(Vector<Vector<Edge> >& adjList){
        int n=adjList.size();
        Vector<bool> tra(n,false);
        Vector<int> from,to;
        PriorityQueue<Edge> pQ;
        pQ.push(Edge(0,0));
        while(pQ.size()){
            int cur=pQ.top().to;
            int dist=pQ.top().dist;
            int prev=pQ.top().from;
            pQ.pop();
            if(tra[cur]) continue;
            from.push_back(prev);
            to.push_back(cur);
            tra[cur]=true;
            for(int cnt=0;cnt<adjList[cur].size();cnt++){
                if(!tra[adjList[cur][cnt].to]){
                    pQ.push(Edge(adjList[cur][cnt].to,
                                 adjList[cur][cnt].dist,
                                 cur));
                }
            }
        }
        if(from.size()<n)printf("No spanning tree.\n");
        else{
            for(int cnt=1;cnt<from.size();cnt++){
                if(cnt>1)printf(" ");
                printf("(%d, %d);",from[cnt],to[cnt]);
            }
            printf("\n");
        }
    return;
}
**/

/// Dijkstra Algorithm
/// Use Priority Queue to optimize
/// Outline:-----------------------------------------------------------------
/// Given query (a,b) to search for the shortest path from a to b
/// We start out by push "a" into the Priority Queue.
/// The Priority Queue is ordered by the current traversed distance
/// of the node starting from "a".
/// Each time, extract an element from the Priority Queue,
/// update the shortest path of its adjacent node, and mark
/// the element as traversed.
/// After each walkable node is traversed, the shortest path, if existent
/// will be found.
void query(Vector<Vector<Edge> >& adjList,int a, int b){
    if(a==b){
        printf("(%d, %d);\n",a,b);
        return;
    }
    int n=adjList.size();
    Vector<int> prev(n,-1);
    Vector<bool> tra(n,false);
    Vector<int> dist(n,INF);
    PriorityQueue<Edge> pQ;
    dist[a]=0;
    pQ.push(Edge(a,0));
    while(pQ.size()){
        int cur=pQ.top().to;
        int curDist=pQ.top().dist;
        pQ.pop();
        tra[cur]=true;
        for(int cnt=0;cnt<adjList[cur].size();cnt++)
            if(!tra[adjList[cur][cnt].to]){
                int to=adjList[cur][cnt].to;
                int newDist=adjList[cur][cnt].dist+curDist;
                if(newDist<dist[to]){
                    dist[to]=newDist;
                    prev[to]=cur;
                    pQ.push(Edge(to,newDist));
                }

            }
    }
    Vector<int> stak;
    int cur=b;
    if(prev[b]==-1){
        printf("Not exist\n");
        return;
    }
    while(1){
        stak.push_back(cur);
        if(cur==a) break;
        cur=prev[cur];

    }
    for(int cnt=stak.size()-1;cnt;--cnt){
        if(cnt!=stak.size()-1) printf(" ");
        printf("(%d, %d);",stak[cnt],stak[cnt-1]);
    }
    printf("\n");
    return;
}

int main(int argc, char *argv[]){
    if(argc<2)return 1;
    fstream fin(argv[1],ios::in);
    bool loop=true;
    while(loop){
        int n,m;
        fin>>n>>m;
        // Build List
        Vector<Vector<Edge> > adjList(n);
        for(int cnt=0;cnt<m;cnt++){
            int w,a,b;
            fin>>a>>b>>w;
            adjList[a].push_back(Edge(b,w));
            adjList[b].push_back(Edge(a,w));
        }
        while(fin.get()!='\n');
        spanning(adjList);

        while(1){
            // Query
            int a,b;
            a=fin.get();
            if(a=='Z'||a=='z')break;
            if(a=='X'||a=='x'){
                loop=false;
                break;
            }
            fin.putback(a);
            fin>>a>>b;
            query(adjList,a,b);
            while(fin.get()!='\n');
        }
        printf("\n");
    }
    fin.close();
    return 0;
}
