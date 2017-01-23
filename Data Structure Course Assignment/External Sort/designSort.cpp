#include <bits/stdc++.h>
#define bucketSize 10
using namespace std;

string digit[]={"0","1","2","3","4","5","6","7","8","9"};

int main(int argc, char* argv[]){
    if(argc<3) return 1;
    fstream fin, ftime,fout;
    fin.open(argv[1],ios::in);
    ftime.open(argv[2],ios::out);
    ftime<<fixed<<setprecision(5);
    clock_t clkBase=clock();
    fstream buffer("buffer",ios::out|ios::binary);
    unsigned int bitLen=0;
    while(1){
        unsigned int temp;
        fin>>temp;
        if(temp==0) break;
        bitLen=max(bitLen,temp);
        buffer.write((char*)&temp,sizeof(unsigned int));
    }
    fin.close();
    buffer.close();
    bitLen=log10(max(bitLen,10u))+1;
    unsigned long long int base=1;
    for(int bit=0;bit<bitLen;bit++){
        buffer.clear();
        buffer.open("buffer",ios::in|ios::binary);
        vector<fstream> bucket(bucketSize);
        for(int cnt=0;cnt<bucketSize;cnt++)
            bucket[cnt].open(digit[cnt]+".bucket",ios::out|ios::binary);
        while(1){
            unsigned int temp;
            if(buffer.read((char*)&temp,sizeof(unsigned int))==0)break;
            bucket[temp/base%bucketSize].write((char*)&temp,sizeof(unsigned int));
        }
        buffer.close(); buffer.clear();
        buffer.open("buffer",ios::out|ios::binary);
        for(int cnt=0;cnt<bucketSize;cnt++){
            bucket[cnt].close();
            bucket[cnt].clear();
            bucket[cnt].open(digit[cnt]+".bucket",ios::in|ios::binary);
        }
        for(int cnt=0;cnt<bucketSize;cnt++)
        while(1){
            unsigned int temp;
            if(bucket[cnt].read((char*)&temp,sizeof(unsigned int))==0)break;
            buffer.write((char*)&temp,sizeof(unsigned int));
        }
        for(int cnt=0;cnt<bucketSize;cnt++)
            bucket[cnt].close();
        buffer.close();
        base*=bucketSize;
    }
    ftime<<(double)(clock()-clkBase)/CLOCKS_PER_SEC<<"\n";
    fout.open(argv[3],ios::out);
    buffer.clear();
    buffer.open("buffer",ios::in|ios::binary);
    for(bool cnt=false;;cnt=true){
        unsigned int temp;
        if(buffer.read((char*)&temp,sizeof(unsigned int))==0)break;
        if(cnt)fout<<" ";
        fout<<temp;
    }
    fout<<"\n";
    fout.close();
    buffer.close();
    remove("buffer");
    for(int cnt=0;cnt<bucketSize;cnt++)
        remove((digit[cnt]+".bucket").c_str());
    return 0;
}
