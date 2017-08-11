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
    };
public:
    SparseMatrix(int n=1, int m=1):n(n),m(m), mat(n){}
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
};

int main(){
    SparseMatrix A(3,3);
    A(0,0);
    A(1,1) = 2;
    A(2,1) = 3;
    auto B = A.transpose();
    B = B*A+A;
    for(int i=0;i<3;++i, printf("\n"))
    for(int j=0;j<3;++j)
        cout<<B(i,j)<<", ";

}
