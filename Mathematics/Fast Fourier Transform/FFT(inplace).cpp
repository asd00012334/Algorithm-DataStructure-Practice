template<typename iter>
void split(iter begin, iter end){
    /// Assume end-begin is 2 power
    int hsize = (end-begin)>>1;
    if(hsize<=1) return;
    iter mid = begin+hsize;
    split(begin,mid);
    split(mid,end);
    begin+=hsize>>=1;
    for(int i=0;i<hsize;++i)
        swap(begin[i],mid[i]);
}

template<typename iter>
void fft(iter begin, iter end){
    /// Assume end-begin is 2 power
    typedef typename iter::value_type type;
    int size = end-begin;
    if(size==1 || size==0) return;
    split(begin,end);
    int hsize = size>>1;
    iter mid = begin+hsize;
    fft(begin,mid); fft(mid,end);
    static const double pi = acos(-1);
    type w = 1, dw = exp(type(0,-2*pi/size));
    for(int k=0;k<hsize;k++, w*=dw){
        type even = begin[k], odd = w*mid[k];
        begin[k] = even+odd;
        mid[k] = even-odd;
    }
}

template<typename iter>
void ifft(iter begin, iter end){
    /// Assume end-begin is 2 power
    typedef typename iter::value_type type;
    int size = end-begin;
    if(size==1 || size==0) return;
    split(begin,end);
    int hsize = size>>1;
    iter mid = begin+hsize;
    ifft(begin,mid); ifft(mid,end);
    static const double pi = acos(-1);
    type w = 1, dw = exp(type(0,2*pi/size));
    for(int k=0;k<hsize;k++, w*=dw){
        type even = begin[k], odd = w*mid[k];
        begin[k] = (even+odd)/type(2);
        mid[k] = (even-odd)/type(2);
    }
}
