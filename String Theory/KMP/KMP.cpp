#include <bits/stdc++.h>

using namespace std;

int KMP(string const& T, string const& P){
    if(T.size()<P.size()||T.size()==0||P.size()==0) return EOF;
    int txt, pat;
    vector<int> prefix(P.size());
    pat=1;
    prefix[0]=0;
    while(pat<P.size()){
        int pre=prefix[pat-1];
        while(pre>0&&P[pre]!=P[pat])
            pre = prefix[pre-1];
        prefix[pat] = pre;
        if(P[pre]==P[pat])
            prefix[pat]++;
        pat++;
    }
    txt=pat=0;
    while(txt<T.size()&&pat<P.size()){
        if(T[txt]==P[pat]){
            txt++;
            pat++;
        }
        else{
            if(pat) pat=prefix[pat-1];
            else txt++;
        }
    }
    if(pat==P.size()) return txt-pat;
    return EOF;
}



int main(){
    cout<<KMP("This is a KMP algorithm.","is is")<<endl;
    return 0;
}
