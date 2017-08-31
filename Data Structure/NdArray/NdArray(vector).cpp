#include<bits/stdc++.h>

using namespace std;

template<int dim, typename type>
struct NdArray{
    typedef std::vector<typename NdArray<dim-1,type>::vector> vector;
    static vector build(int const width[]){
        return vector(*width,NdArray<dim-1,type>::build(width+1));
    }
};

template<typename type>
struct NdArray<1,type>{
    typedef std::vector<type> vector;
    static vector build(int const width[]){return vector(*width);}
};

int main(){
    auto a = NdArray<2,int>::build((int const[]){10,10});
    for(int i=0;i<10;++i,cout<<"\n")
    for(int j=0;j<10;++j)
        cout<<(a[i][j]=10*i+j)<<" ";
    cout<<"\n";
    for(int i=0;i<10;++i,cout<<"\n")
    for(int j=0;j<10;++j)
        cout<<(a[i][j])<<" ";
}

