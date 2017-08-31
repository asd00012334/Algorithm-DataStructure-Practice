#include<bits/stdc++.h>

using namespace std;

/// Recursively Generate Pointer Type
/// i.e. addStar<3,type>::ptr = type***
template<int dim, typename type>
struct addStar{
    typedef typename addStar<dim-1,type>::ptr* ptr;
};

template<typename type>
struct addStar<0,type>{
    typedef type ptr;
};

/// Calculate total size of the memory pool for an ND-Array
template<int dim, typename type>
struct memSize{
    static inline void set(int const width[], int mem[]){
        memSize<dim-1,type>::set(width+1,mem);
        mem[dim]=(*width)*(mem[dim-1]+sizeof(typename addStar<dim-1,type>::ptr));
    }
};

template<typename type>
struct memSize<1,type>{
    static inline void set(int const width[], int mem[]){
        mem[0] = sizeof(type);
        mem[1] = (*width)*sizeof(type);
    }
};

/// Set up pointers in memory pool
template<int dim,typename type>
struct setPtr{
    static inline void set(typename addStar<dim,type>::ptr ptr,int const width[], int mem[]){
        for(int i=0;i<*width;++i){
            ptr[i] = (typename addStar<dim-1,type>::ptr)(ptr+*width)+mem[dim-1]*i;
            setPtr<dim-1,type>::set(ptr[i],width+1,mem);
        }
    };
};

template<typename type>
struct setPtr<1,type>{
    static inline void set(typename addStar<1,type>::ptr ptr, int const width[],int mem[]){}
};

/// Dynamically Generate const-dimensional array
template<int dim, typename type>
typename addStar<dim, type>::ptr buildNd(int const width[]){
    int mem[dim+1];
    memSize<dim,type>::set(width,mem);
    auto retPtr = (typename addStar<dim,type>::ptr) new char[mem[dim]];
    setPtr<dim,type>::set(retPtr,width,mem);
    return retPtr;
}


int main(){
    auto a = buildNd<2,int>((int const[]){10,10});
    for(int i=0;i<10;++i,cout<<"\n")
    for(int j=0;j<10;++j)
        cout<<(a[i][j]=10*i+j)<<" ";
    cout<<"\n";
    for(int i=0;i<10;++i,cout<<"\n")
    for(int j=0;j<10;++j)
        cout<<(a[i][j])<<" ";
    delete a;
}

