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

/// Sum out const-size non-empty array
/// i.e. sum<5, int>::get(arr) = arr[0]+arr[1]+...+arr[4]
template<int size, typename type>
struct sum{
    static inline type get(type const arr[]){
        return *arr+sum<size-1,type>::get(arr+1);
    }
};

template<typename type>
struct sum<0,type>{
    static inline type get(type const arr[]){
        return type();
    }
};

/// Calculate total size of the memory pool for an ND-Array
template<int dep, typename type>
struct memSize{
    static inline void set(int const width[], int mem[]){
        memSize<dep-1,type>::set(width+1,mem);
        mem[dep]=mem[dep-1]* *width;
    }
};

template<typename type>
struct memSize<0,type>{
    static inline void set(int const width[], int mem[]){
        mem[0] = 1;
    }
};

/// Set up pointers in memory pool
template<int dim,typename type>
struct setPtr{
    static inline void set(char* ptr,int const width[], int mem[]){
        for(int i=0;i<*mem;++i){
            ((char**)ptr)[i] = ptr+(*mem+*width*i)*sizeof(char*);
        }
        setPtr<dim-1,type>::set(ptr+*mem*sizeof(char*),width+1,mem+1);
    };
};

template<typename type>
struct setPtr<1,type>{
    static inline void set(char* ptr, int const width[],int mem[]){
        for(int i=0;i<*mem;++i){
            ((char**)ptr)[i] = ptr+(*mem+*width*i)*sizeof(type);
        }
    }
};

/// Dynamically Generate const-dimensional array
template<int dim, typename type>
auto buildNd(int const width[]){
    int mem[dim+1];
    memSize<dim,type>::set(width,mem);
    char* retPtr = new char[sum<dim-1,int>::get(mem+1)*sizeof(char*)+mem[dim]*sizeof(type)];
    setPtr<dim-1,type>::set(retPtr,width+1,mem+1);
    return (typename addStar<dim, type>::ptr)retPtr;
}

int main(){
    auto a = buildNd<2,int>((int const[]){10,10});
    auto aLinear = &a[0][0];
    for(int i=0;i<10;++i,cout<<"\n")
    for(int j=0;j<10;++j)
        cout<<(a[i][j]=10*i+j)<<" ";
    for(int i=0;i<10;++i,cout<<"\n")
    for(int j=0;j<10;++j)
        cout<<(aLinear[i*10+j])<<" ";
    delete a;
}

