#include <bits/stdc++.h>

using namespace std;

template<typename iter>
void quickSort(iter begin, iter end){
    if(end-begin<=1) return;
    iter form = begin+1;
    iter latt = end-1;
    while(form<=latt)
        if(*form<*begin) ++form;
        else if(*begin<*latt) --latt;
        else swap(*form,*(latt--));
    swap(*begin,*latt);
    quickSort(begin,latt);
    quickSort(form,end);
}


int main(){
    string input = "This is a Quick Sort.";
    quickSort(input.begin(),input.end());
    cout<<input<<endl;
    return 0;
}
