#include <bits/stdc++.h>

using namespace std;

template<typename container>
int lengthLCS(container const& left, container const& right){
    int LCS[left.size()+1][right.size()+1];
    for(int l = 0;l<=left.size(); l++)
    for(int r = 0;r<=right.size(); r++)
        if(!l||!r) LCS[l][r] = 0;
        else
            if(!(left[l-1]<right[r-1])&&!(right[r-1]<left[l-1]))
                LCS[l][r] = LCS[l-1][r-1]+1;
            else
                LCS[l][r] = max(LCS[l-1][r], LCS[l][r-1]);
    return LCS[left.size()][right.size()];
}

int main(){
    vector<int> a = {9,3,6,7,2,4};
    vector<int> b = {7,9,2,4,6};
    cout<<lengthLCS(a,b)<<endl;
    return 0;
}
