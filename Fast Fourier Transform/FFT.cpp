#include<bits/stdc++.h>

using namespace std;

template<typename type>
void substitute(vector<complex<type> > const& seq, complex<type> omega){
    if(seq.size()==1) return;
    vector<complex<type> > odd(seq.size()/2);
    vector<complex<type> > even(seq.size()-odd.size());
    for(int cnt=0;cnt<seq.size();cnt++){
        if(cnt%2) odd[cnt/2]=seq[cnt];
        else even[cnt/2]=seq[cnt];
    }
    complex<type> w2=omega*omega;
    substitute(even,w2);
    substitute(odd,w2);
    for(int cnt=0;cnt<seq.size();cnt++)
        seq[cnt]=even[cnt/2]+omega*odd[cnt/2];
}

template<typename type>
void fourier(vector<complex<type> >& seq){
    if(seq.empty()) return;
    vector<complex<type> > out(seq.size());
    seq.resize(pow(2,ceil(log2(seq.size()))),0);
    complex<type> i(0,1);
    complex<type> pi(acos(0)*2,0);
    complex<type> omega(exp(-i*2*pi/seq.size()));
    substitute(seq,omega);
    type base=sqrt(seq.size());
    for(int cnt=0;cnt<seq.size();cnt++)
        seq[cnt]/=base;
}

template<typename type>
void invFourier(vector<complex<type> >& seq){
    if(seq.empty()) return;
    vector<complex<type> > out(seq.size());
    seq.resize(pow(2,ceil(log2(seq.size()))),0);
    complex<type> i(0,1);
    complex<type> pi(acos(0)*2,0);
    complex<type> omega(exp(i*2*pi/seq.size()));
    substitute(seq,omega);
    type base=sqrt(seq.size());
    for(int cnt=0;cnt<seq.size();cnt++)
        seq[cnt]/=base;
}


int main(){
    /** Experimental **/

    return 0;
}
