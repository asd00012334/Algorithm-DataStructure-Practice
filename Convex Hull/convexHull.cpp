#include<bits/stdc++.h>

using namespace std;

template<class Cont>
inline void interChange(Cont& s){
    for(int cnt=0;cnt<s.size();cnt++)
        swap(s[cnt].first,s[cnt].second);
}

pair<int,int> operator-(pair<int,int> const& l, pair<int,int> const& r){
    return pair<int,int>(l.first-r.first,l.second-r.second);
}

template<class Pt>
int cross(Pt& l, Pt& r){
    return l.first*r.second-l.second*r.first;
}

template<class Cont>
void push(Cont& src, Cont& tar){
    for(int cnt=0;cnt<src.size();cnt++)
        tar.push_back(src[cnt]);
}

template<class Iter, class Cont>
void pushHalf(Iter const& s, Cont& c,int size){
    vector<pair<int,int> > half;
    for(int cnt=0;cnt<size;){
        if(half.size()<2) half.push_back(s[cnt++]);
        else{
            auto prev = half.back()-half[half.size()-2];
            auto nxt = s[cnt]-half.back();
            if(cross(prev,nxt)>0) half.push_back(s[cnt++]);
            else half.pop_back();
        }
    }
    push(half,c);
    c.pop_back();
}

void convexHull(vector<pair<int,int> > &s, vector<pair<int,int> > &c){
    sort(s.begin(),s.end());
    pushHalf(s.begin(),c,s.size());
    pushHalf(s.rbegin(),c,s.size());
}


int main(){
    vector<pair<int,int> >  s{{0,0},{3,0},{0,3},{-3,0},{0,-3},{1,1},{-1,-1},{-1,1},{1,-1},{1,0},{-1,0}},c;
    convexHull(s,c);
    for(int cnt=0;cnt<c.size();cnt++)
        printf("(%d,%d)",c[cnt].first,c[cnt].second);
}
