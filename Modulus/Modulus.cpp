#include <bits/stdc++.h>

using namespace std;

template<typename type>
type GCD(type left, type right){
    if(!left && !right) throw logic_error("Return value does not exist.\n");
    left = abs(left);
    right = abs(right);
    return left?GCD(right%left,left):right;
}

template<typename type>
type LCM(type left, type right){
    if(!left || !right) throw logic_error("Return value does not exist.\n");
    return abs(left*right/GCD(left,right));
}

template<typename type>
pair<type,type> extGCD(type left, type right){
    if(!left && !right) throw logic_error("Return value does not exist.\n");
    pair<type,type> lCor(1,0), rCor(0,1);
    if(left<0) lCor.first = -1;
    if(right<0) rCor.second = -1;
    left = abs(left);
    right = abs(right);
    while(left){
        swap(lCor,rCor);
        swap(left,right);
        lCor.first -= left/right*rCor.first;
        lCor.second -= left/right*rCor.second;
        left %= right;
    }
    return rCor;
}

template<typename type>
type modulusInverse(type input, type mod){
    pair<type,type> p = extGCD(input,mod);
    if(input*p.first+mod*p.second!=1)
        throw logic_error("Return value does not exist.\n");
    if(p.first<0) p.first = p.first%mod+mod;
    return p.first;
}


int main(){
    srand(time(NULL));
    for(int cnt=0;cnt<100;cnt++){
        int left,right;
        left=rand()%250;
        right=rand()%50;
        pair<int,int> p = extGCD(left,right);
        printf("GCD(%d,%d) = %d\n",left,right,GCD(left,right));
        printf("LCM(%d,%d) = %d\n",left,right,LCM(left,right));
        printf("extGCD(%d,%d) = (%d,%d)\n",left,right,p.first,p.second);
        printf("Reverse Modulus of %d under modulus %d: ",left,right);
        if(GCD(left,right)==1)
            printf("%d + %dn\n",modulusInverse(left,right),right);
        else
            printf("Not Exist\n");

        printf("\n");
    }
    return 0;
}
