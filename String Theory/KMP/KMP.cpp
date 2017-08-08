#include<bits/stdc++.h>

using namespace std;
/// Yet to be tested
vector<int> fail;
void build(string const& str){
    fail = vector<int>(str.size(),-1);
    for(int cnt=1;cnt<str.size();++cnt){
        int pivot = fail[cnt-1];
        while(pivot!=-1 && str[pivot+1]!=str[cnt])
            pivot = fail[pivot];
        if(str[pivot+1]==str[cnt]) fail[cnt]=pivot+1;
        else fail[cnt]=-1;
    }
}
bool KMP(string const& s, string const& p, vector<int>& match){
    build(p);
    match = vector<int>();
    int pos=-1;
    for(int cnt=0;cnt<s.size();++cnt){
        if(s[cnt]==p[pos+1]) ++pos;
        else if(pos!=-1) pos=fail[pos], --cnt;
        if(pos==p.size()-1){
            match.push_back(cnt);
            pos = fail[pos];
        }
    }
}


int main(){
    string s("aaabaabbabb"), p("aa");
    vector<int> match;
    KMP(s,p,match);
    for(int cnt=0;cnt<match.size();++cnt)
        printf("%d ",match[cnt]);
    printf("\n");
}
