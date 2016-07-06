#include <bits/stdc++.h>

using namespace std;

template<typename iter>
void quickSort(iter begin, iter end){
    static int randGenerated = 0;
    int size = end-begin;
    if(size<=1) return;
    if(!randGenerated) srand(time(NULL));
    randGenerated = (randGenerated+1)%50000;
    swap(begin[0],begin[rand()%size]);
    iter form = begin+1;
    iter latt = begin+size-1;
    while(form<=latt)
        if(*form<*begin)
            ++form;
        else if(*begin<*latt)
            --latt;
        else
            swap(*form,*(latt--));
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
