#include<bits/stdc++.h>

using namespace std;

void cholesky(
    vector<vector<double> > const& A,
    vector<vector<double> >&L
){
    int n = A.size();
    L = vector<vector<double> >(n, vector<double>(n,0));
    for(int i=0;i<n;++i){
        for(int j=0;j<i;++j){
            L[i][j] = A[i][j];
            for(int k=0;k<j;++k)
                L[i][j]-=L[i][k]*L[j][k];
            L[i][j]/=L[j][j];
        }
        L[i][i] = A[i][i];
        for(int k=0;k<i;++k)
            L[i][i]-=L[i][k]*L[i][k];
        L[i][i]=sqrt(L[i][i]);
    }
}

void solve(
    vector<vector<double> > const& A,
    vector<double>& x,
    vector<double> const& b
){
    int n = A.size();
    vector<vector<double> > L;
    cholesky(A,L);
    x = b;
    for(int i=0;i<n;++i){
        x[i]/=L[i][i];
        for(int k=i+1;k<n;++k)
            x[k]-=L[k][i]*x[i];
    }
    for(int i=n-1;i>=0;--i){
        x[i]/=L[i][i];
        for(int k=i-1;k>=0;--k)
            x[k]-=L[i][k]*x[i];
    }
}

int main(){
    vector<vector<double> > A{
        {4,-2,4,2},
        {-2,10,-2,-7},
        {4,-2,8,4},
        {2,-7,4,7}
    };
    vector<double> b{1,2,7,9},x;
    solve(A,x,b);
    for(int cnt=0;cnt<x.size();++cnt)
        cout<<x[cnt]<<"\n";
    return 0;
}
