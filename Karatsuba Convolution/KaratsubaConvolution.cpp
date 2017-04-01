#include<bits/stdc++.h>
#define threshold 16
using namespace std;

template<typename type>
void convKernel(vector<type>& l, vector<type>& r, vector<type>& result){
    /// Assume l.size() == r.size() == pow(2,k)
    /// Assume left as low bit and right as high bit
    int size=l.size();
    result=vector<type>(size*2,0);
    if(size<=threshold){
        for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            result[i+j]+=l[i]*r[j];
        return;
    }
    int hSize=size/2;
    vector<type> ll(hSize), rl(hSize);
    vector<type> lr(hSize), rr(hSize);
    vector<type> lmix(hSize), rmix(hSize);
    for(int cnt=0;cnt<size;cnt++){
        if(cnt<hSize){
            ll[cnt]=l[cnt];
            rl[cnt]=r[cnt];
            lmix[cnt]=l[cnt];
            rmix[cnt]=r[cnt];
        } else{
            lr[cnt-hSize]=l[cnt];
            rr[cnt-hSize]=r[cnt];
            lmix[cnt-hSize]+=l[cnt];
            rmix[cnt-hSize]+=r[cnt];
        }
    }
    vector<type> leftResult, mixResult, rightResult;
    convKernel(ll,rl,leftResult);
    convKernel(lr,rr,rightResult);
    convKernel(lmix,rmix,mixResult);

    for(int cnt=0;cnt<size;cnt++){
        result[cnt+hSize*2]+=rightResult[cnt];
        result[cnt+hSize]+=mixResult[cnt]-rightResult[cnt]-leftResult[cnt];
        result[cnt]+=leftResult[cnt];
    }
}

template<typename type>
void conv(vector<type>& l, vector<type>& r, vector<type>& result){
    int n=max(l.size(),r.size());
    n=pow(2,ceil(log2(n)));
    l.resize(n,0);
    r.resize(n,0);
    convKernel(l,r,result);
}

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> l(n,0);
        vector<int> r(n,0);
        for(int cnt=0;cnt<n;cnt++)
            scanf("%d",&l[cnt]);
        for(int cnt=0;cnt<n;cnt++)
            scanf("%d",&r[cnt]);
        vector<int> result(l.size()+r.size());
        conv(l,r,result);
        for(int cnt=0;cnt<2*n-1;cnt++){
            if(cnt) printf(" ");
            printf("%d",result[cnt]);
        }
        printf("\n");
    }


    return 0;
}

