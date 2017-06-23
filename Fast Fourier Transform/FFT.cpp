#include <bits/stdc++.h>

using namespace std;

template<class Cont>
void fft(Cont& x){
    typedef typename Cont::value_type type;
    int size = x.size();
    if(size==1 || size==0) return;
    if(size&(size-1)) x.resize(size = 1<<__lg(size<<1),0);
    Cont even(size>>1), odd(size+1>>1);
    for(int n=0;n<size;n++)
        if(n&1) odd[n>>1] = x[n];
        else even[n>>1] = x[n];
    fft(even);
    fft(odd);
    const double pi = acos(-1);
    for(int k=0;k<size;k++)
        x[k] = (
            even[k%even.size()]+
            exp(-type(0,-k*2*pi/size)*odd[k%odd.size()])
        )/type(2);
}

template<class Cont>
void ifft(Cont& x){
    typedef typename Cont::value_type type;
    int size = x.size();
    if(size==1 || size==0) return;
    if(size&(size-1)) x.resize(size = 1<<__lg(size<<1),0);
    Cont even(size>>1), odd(size+1>>1);
    for(int n=0;n<size;n++)
        if(n&1) odd[n>>1] = x[n];
        else even[n>>1] = x[n];
    fft(even);
    fft(odd);
    const double pi = acos(-1);
    for(int k=0;k<size;k++)
        x[k] = (
            even[k%even.size()]+
            exp(type(0,-k*2*pi/size)*odd[k%odd.size()])
        );
}

int main(){
    double Ts = 0.001;
    double T = 100;
    double const pi = acos(-1);
    int N = T/Ts;
    vector<double> x(N);
    vector<double> y(N);
    for(int cnt=0;cnt<N;cnt++){
        x[cnt] = cnt*Ts;
        y[cnt] = cos(2*pi*x[cnt]*5);
    }
    vector<complex<double> > f(y.begin(),y.end());
    for(int cnt=0;cnt<10;cnt++)
        cout<<y[cnt]<<" ";
    cout<<endl;
    fft(f);
    ifft(f);
    for(int cnt=0;cnt<10;cnt++)
        cout<<y[cnt]<<" ";
    return 0;
}
