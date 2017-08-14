#include<bits/stdc++.h>
#define eps (1e-9)
using namespace std;

class SparseMatrix{
    int n,m;
    vector<map<int,double> > mat;
    class Entry{
        int i, j;
        SparseMatrix* container;
        double* elem;
        void setZero(){
            if(!elem) return;
            elem=NULL;
            container->mat[i].erase(j);
        }
    public:
        Entry(int i, int j, SparseMatrix* container, double* elem=NULL):
            i(i), j(j), container(container), elem(elem){}
        Entry& operator=(double val){
            if(abs(val)<eps){ setZero(); return *this;}
            if(elem) *elem=val;
            else elem=&(container->mat[i][j]=val);
            return *this;
        }
        operator double(){
            if(elem) return *elem;
            return 0;
        }
        double& operator=(Entry a){ (*this)=double(a);}
        double& operator+=(double a){ (*container)(i,j) = (*container)(i,j)+a;}
        double& operator-=(double a){ (*container)(i,j) = (*container)(i,j)-a;}
        double& operator*=(double a){ (*container)(i,j) = (*container)(i,j)*a;}
        double& operator/=(double a){ (*container)(i,j) = (*container)(i,j)/a;}
    };
public:
    SparseMatrix(int n=1, int m=1):n(n),m(m), mat(n){}
    SparseMatrix(vector<vector<double> > const&init){
        if(init.empty()) throw exception();
        n=init.size(), m=init[0].size();
        mat.resize(n);
        for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            (*this)(i,j)=init[i][j];
    }
    Entry operator()(int i, int j){
        if(i<0 || j<0 || i>=n || j>=m) throw exception();
        if(mat[i].count(j)) return Entry(i,j,this,&mat[i][j]);
        return Entry(i,j,this,NULL);
    }
    SparseMatrix transpose()const{
        SparseMatrix out(m,n);
        for(int r=0;r<n;++r)
        for(map<int,double>::const_iterator iter=mat[r].begin();iter!=mat[r].end();++iter)
            out(iter->first,r) = iter->second;
        return out;
    }
    friend SparseMatrix operator*(SparseMatrix const& L, SparseMatrix const& R){
        if(L.m!=R.n) throw exception();
        int n=L.n, m=R.m;
        SparseMatrix const rT = R.transpose();
        SparseMatrix out(n,m);
        for(int r=0;r<n;++r)
        for(int c=0;c<m;++c)
        for(map<int,double>::const_iterator k1=L.mat[r].begin(), k2=rT.mat[c].begin();k1!=L.mat[r].end()&&k2!=rT.mat[c].end();){
            if(k1->first < k2->first) ++k1;
            else if(k2->first < k1->first) ++k2;
            else out(r,c)=out(r,c)+k1->second*k2->second, ++k1, ++k2;
        }
        return out;
    }
    friend SparseMatrix operator+(SparseMatrix const& L, SparseMatrix const& R){
        if(L.n!=R.n || L.m!=R.m) throw exception();
        int n = L.n, m = L.m;
        SparseMatrix out(n,m);
        for(int r=0;r<n;++r){
            for(map<int,double>::const_iterator c=L.mat[r].begin();c!=L.mat[r].end();++c)
                out(r,c->first) = out(r,c->first) + c->second;
            for(map<int,double>::const_iterator c=R.mat[r].begin();c!=R.mat[r].end();++c)
                out(r,c->first) = out(r,c->first) + c->second;
        }
        return out;
    }
    inline friend SparseMatrix operator/(SparseMatrix const& M, double a){ return (1/a)*M;}
    inline friend SparseMatrix operator*(SparseMatrix const& M, double a){ return a*M;}
    friend SparseMatrix operator*(double a,SparseMatrix const& M){
        int n = M.n, m = M.m;
        SparseMatrix out(n,m);
        for(int r=0;r<n;++r)
        for(map<int,double>::const_iterator c=M.mat[r].begin();c!=M.mat[r].end();++c)
            out(r,c->first) = a*c->second;
        return out;
    }
    friend SparseMatrix cholesky(SparseMatrix A){
        if(A.n!=A.m) throw exception();
        int n=A.n;
        SparseMatrix L(n,n);
        for(int i=0;i<n;++i){
            for(int j=0;j<i;++j){
                L(i,j) = A(i,j);
                for(map<int,double>::iterator k1=L.mat[i].begin(), k2=L.mat[j].begin();k1!=L.mat[i].end(), k2!=L.mat[j].end();){
                    if(k1->first>=j||k2->first>=j) break;
                    if(k1->first < k2->first) ++k1;
                    else if(k2->first < k1->first) ++k2;
                    else L(i,j)-=k1->second*k2->second, ++k1, ++k2;
                }
                L(i,j)/=L(j,j);
            }
            L(i,i) = A(i,i);
            for(map<int,double>::iterator k=L.mat[i].begin();k->first<i;++k)
                L(i,i)-=k->second*k->second;
            L(i,i)=sqrt(L(i,i));
        }
        return L;
    }
    friend SparseMatrix cholesky_solve(
        SparseMatrix const& A,
        SparseMatrix const& b
    ){
        int n = A.n;
        SparseMatrix L=cholesky(A);
        SparseMatrix x = b;
        for(int i=0;i<n;++i){
            x(i,0)/=L(i,i);
            for(int k=i+1;k<n;++k)
                x(k,0)-=L(k,i)*x(i,0);
        }
        for(int i=n-1;i>=0;--i){
            x(i,0)/=L(i,i);
            for(int k=i-1;k>=0;--k)
                x(k,0)-=L(i,k)*x(i,0);
        }
        return x;
    }
    friend SparseMatrix conjugate_gradient(
        SparseMatrix A,
        SparseMatrix b
    ){
        int n = A.n;
        SparseMatrix x(n,1);
        SparseMatrix r=b;
        SparseMatrix v=r;
        double betaE;
        double betaD = (r.transpose()*r)(0,0);
        while(n--){
            SparseMatrix vT = v.transpose();
            SparseMatrix Av = A*v;
            double a = betaD/(vT*Av)(0,0);
            x = x+a*v;
            r = r+(-a)*Av;
            betaE = (r.transpose()*r)(0,0);
            v = r+(betaE/betaD)*v;
            betaD = betaE;
        }
        return x;
    }

};

int main(){
    vector<vector<double> > prototype{
        {4,-2,4,2},
        {-2,10,-2,-7},
        {4,-2,8,4},
        {2,-7,4,7}
    }, bp={{1},{2},{7},{9}};
    SparseMatrix A(prototype);
    auto x = conjugate_gradient(A,bp);
    SparseMatrix b=A*x;
    for(int i=0;i<4;++i, printf("\n"))
        cout<<b(i,0)<<", ";
    printf("\n");

}
