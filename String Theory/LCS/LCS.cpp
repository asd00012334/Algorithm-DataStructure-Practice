#include<bits/stdc++.h>

using namespace std;

int LCS(vector<int>& l, vector<int>& r){
    vector<int> length(r.size()+1,0);
    for(int row=1;row<=l.size();row++)
    for(int col=1;col<=r.size();col++){
        if(l[row-1]==r[col-1]) length[col]=length[col-1]+1;
        else length[col] = max(length[col],length[col-1]);
    }
    return length[r.size()];
}

int main(){
    vector<int> a = {9,3,6,7,2,4};
    vector<int> b = {7,9,2,4,6};
    cout<<LCS(a,b)<<endl;
    return 0;
}
