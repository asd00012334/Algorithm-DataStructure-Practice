#include<bits/stdc++.h>
#define ll long long
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


class BigInt{
    bool sign;
    BigInt(ll size, short val): decimal(size,val), sign(true){}
public:
    vector<short> decimal;

    BigInt():decimal(1,0),sign(true){}
    BigInt(string const& str){
        ll base;
        if(str.empty()) throw exception();
        if(str[0]=='-') sign=false, base=1;
        else sign=true, base=0;
        decimal.resize(str.size()-base);
        for(int cnt=0;cnt<decimal.size();cnt++)
            decimal[cnt]=str[str.size()-1-cnt]-'0';
    }
    BigInt(ll const& init){
        sign = init>=0;
        decimal.resize(0);
        for(ll val=abs(init);val;val/=10)
            decimal.push_back(val%10);
        if(decimal.empty()) decimal.push_back(0);
    }
    friend BigInt add(BigInt const& a, BigInt const& b){
        BigInt result(max(a.decimal.size(),b.decimal.size()),0);
        for(int cnt=0;cnt<result.decimal.size();++cnt){
            if(cnt<a.decimal.size()) result.decimal[cnt]+=a.decimal[cnt];
            if(cnt<b.decimal.size()) result.decimal[cnt]+=b.decimal[cnt];
        }
        for(int cnt=0;cnt<result.decimal.size()-1;++cnt)
            if(result.decimal[cnt]>=10) result.decimal[cnt]-=10, ++result.decimal[cnt+1];
        if(result.decimal.size() && result.decimal.back()>=10){
            result.decimal.back()-=10;
            result.decimal.push_back(1);
        }
        return result;
    }
    friend bool smaller(BigInt const& a, BigInt const& b){
        if(a.decimal.size()!=b.decimal.size()) return a.decimal.size()<b.decimal.size();
        for(int cnt=a.decimal.size()-1;cnt>=0;--cnt)
            if(a.decimal[cnt]!=b.decimal[cnt]) return a.decimal[cnt]<b.decimal[cnt];
        return false;
    }
    friend BigInt sub(BigInt a, BigInt b){
        if(smaller(a,b)){
            a.swap(b);
            a.sign=false;
        } else a.sign=true;
        for(int cnt=0;cnt<a.decimal.size();++cnt)
            if(cnt<b.decimal.size()) a.decimal[cnt]-=b.decimal[cnt];
        for(int cnt=0;cnt<a.decimal.size()-1;++cnt)
            if(a.decimal[cnt]<0) a.decimal[cnt]+=10, --a.decimal[cnt+1];
        while(a.decimal.size()&&a.decimal.back()==0) a.decimal.pop_back();
        if(a.decimal.empty()) a.decimal.resize(1,0);
        return a;
    }
    friend BigInt mul(BigInt const& a, BigInt const& b){
        #define eps 1e-6
        ll n = a.decimal.size()+b.decimal.size();
        vector<complex<double> > l(a.decimal.begin(),a.decimal.end()); l.resize(n,0);
        vector<complex<double> > r(b.decimal.begin(),b.decimal.end()); r.resize(n,0);
        fft(l); fft(r); n=l.size();
        for(int cnt=0;cnt<n;cnt++)
            l[cnt]*=r[cnt];
        ifft(l);
        vector<ll> out(n,0);
        for(int cnt=0;cnt<n;++cnt)
            out[cnt] = l[cnt].real()+0.5;
        for(int cnt=0;cnt<n-1;++cnt){
            out[cnt+1]+=out[cnt]/10;
            out[cnt]%=10;
        }
        while(out.size()&&out.back()>=10){
            out.push_back(out.back()/10);
            out[out.size()-2]%=10;
        }
        while(out.size()&&out.back()==0) out.pop_back();
        if(out.empty()) out.resize(1,0);
        BigInt ret(out.size(),0); ret.sign=true;
        for(int cnt=0;cnt<out.size();++cnt)
            ret.decimal[cnt] = out[cnt];
        return ret;
    }
    friend bool operator<(BigInt const& a, BigInt const& b){
        if(a.sign^b.sign) return b.sign;
        bool l1=smaller(a,b), l2=smaller(b,a);
        if(!l1 && !l2) return false;
        return (!a.sign)^l1;
    }
    friend BigInt operator+(BigInt const& a, BigInt const& b){
        BigInt out;
        if(a.sign^b.sign){
            out=sub(a,b);
            if(!out.isZero()&&!a.sign) out.sign=!out.sign;
        } else{
            out=add(a,b);
            out.sign=a.sign;
        }
        return out;
    }
    friend BigInt operator-(BigInt const& a, BigInt const& b){
        BigInt out;
        if(a.sign^b.sign){
            out=add(a,b);
            out.sign=a.sign;
        } else{
            out=sub(a,b);
            if(!out.isZero()&&!a.sign) out.sign=!out.sign;
        }
        return out;
    }
    friend BigInt operator*(BigInt const& a, BigInt const& b){
        BigInt out = mul(a,b);
        if(out.isZero()) out.sign=true;
        else out.sign = !(a.sign^b.sign);
        return out;
    }

    inline bool isZero(){return sign&&decimal.size()==1&&decimal.back()==0;}
    void dump() const{
        if(!sign) printf("-");
        for(int cnt=decimal.size()-1;cnt>=0;--cnt)
            printf("%d",decimal[cnt]);
    }
    void swap(BigInt& b){
        std::swap(sign,b.sign);
        decimal.swap(b.decimal);
    }

};


int main(){
    int t;
    cin>>t;
    while(t--){
        string lstr, rstr;
        cin>>lstr>>rstr;
        ((BigInt)lstr*rstr).dump();
        printf("\n");
    }
}
