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

int main(){
    return 0;
}
