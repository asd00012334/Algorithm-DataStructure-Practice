#include <bits/stdc++.h>

using namespace std;

template<class Cont>
void fft(Cont& x){
    typedef typename Cont::value_type type;
    int size = x.size();
    if(size==1 || size==0) return;
    if(size&(size-1)) x.resize(size = 1<<__lg(size<<1),0);
    Cont even(size>>1), odd(size>>1);
    for(int n=0;n<size;n++)
        if(n&1) odd[n>>1] = x[n];
        else even[n>>1] = x[n];
    fft(even);
    fft(odd);
    static const double pi = acos(-1);
    type w = 1, dw = exp(type(0,-2*pi/size));
    for(int k=0;k<size;k++, w*=dw)
        x[k] = even[k%even.size()] + w*odd[k%odd.size()];
}

template<class Cont>
void ifft(Cont& x){
    typedef typename Cont::value_type type;
    int size = x.size();
    if(size==1 || size==0) return;
    if(size&(size-1)) x.resize(size = 1<<__lg(size<<1),0);
    Cont even(size>>1), odd(size+1>>1);
    for(int k=0;k<size;k++)
        if(k&1) odd[k>>1] = x[k];
        else even[k>>1] = x[k];
    ifft(even);
    ifft(odd);
    static const double pi = acos(-1);
    type w = 1, dw = exp(type(0,2*pi/size));
    for(int k=0;k<size;k++, w*=dw)
        x[k] = (even[k%even.size()] + w*odd[k%odd.size()])/type(2);
}

int main(){
    double Ts = 0.001;
    int N = 1<<18;
    double T = N*Ts;
    double const pi = acos(-1);
    vector<double> x(N);
    vector<double> y(N);
    for(int cnt=0;cnt<N;cnt++){
        x[cnt] = cnt*Ts;
        y[cnt] = cos(2*pi*x[cnt]*200);
    }
    vector<complex<double> > f(y.begin(),y.end());
    fft(f);
    ifft(f);
    return 0;
}
