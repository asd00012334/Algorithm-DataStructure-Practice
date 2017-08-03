#include <bits/stdc++.h>
#define sampleNum 500
using namespace std;

pair<int,int> countAB(int n, int guess){
    /// (a,b)
    int realA=0, realB=0;
    int stat[10]={};
    for(int cnt=0, temp=n;cnt<4;cnt++){
        stat[temp%10]++;
        temp/=10;
    }
    for(int cnt=0;cnt<4;cnt++){
        if(stat[guess%10]>0){
            stat[guess%10]--;
            if(n%10==guess%10) realA++;
            else realB++;
        }
        guess/=10;
        n/=10;
    }
    return pair<int,int>(realA,realB);
}

bool legal(int n, int guess, int a, int b){
    pair<int,int> ab = countAB(n,guess);
    return ab.first==a && ab.second==b;
}

void trim(vector<int>& remain, int guess, int a, int b){
    int size=0;
    for(int cnt=0;cnt<remain.size();cnt++)
        if(legal(remain[cnt],guess,a,b))
            remain[size++]=remain[cnt];
    remain.resize(size);
}

int trimCnt(vector<int>::iterator remain, vector<int>::iterator remainEnd, int guess, int a, int b){
    int size=remainEnd-remain;
    int total=0;
    for(int cnt=0;cnt<size;++cnt)
        if(legal(remain[cnt],guess,a,b))
            ++total;
    return total;
}

void decompose(vector<int>& decomp, int n, int round){
    decomp.resize(round);
    for(int cnt=0;cnt<round;cnt++, n/=10)
        decomp[cnt] = n%round;
}

int compose(vector<int> const& decomp){
    int out=0;
    for(int cnt=0;cnt<decomp.size();cnt++)
        out = out*10+decomp[cnt];
    return out;
}

int takeGuess(vector<int>& remain, int t){
    /// O(n^3)
    static vector<int> prev;
    if(t==1){
        prev.clear();
        int guess = remain[rand()%remain.size()];
        prev.push_back(guess);
        return guess;
    }
    int n = min(sampleNum,(int)remain.size());
    vector<int> &arr = remain;
    for(int cnt=0;cnt<arr.size();cnt++)
        swap(arr[cnt],arr[rand()%arr.size()]);
    vector<double> etps(n,0);
    set<int> symmetry;
    for(int cnt=0;cnt<n;cnt++){
        if(symmetry.count(arr[cnt])) continue;
        for(int ansIdx=0;ansIdx<n;ansIdx++){
            pair<int,int> ab = countAB(arr[ansIdx],arr[cnt]);
            int heuristic = trimCnt(arr.begin(),arr.begin()+n,arr[cnt],ab.first,ab.second);
            etps[cnt]+=log2(heuristic);//heuristic;
        }
        if(t==2){/// Symmetry Optimization
            set<int> clr;
            vector<int> decomp;
            decompose(decomp,prev[0],4);
            for(int i=0;i<decomp.size();i++)
                clr.insert(decomp[i]);
            int temp = arr[cnt];
            decompose(decomp,temp,4);
            for(int i=0;i<decomp.size();i++)
                if(clr.count(decomp[i])) decomp[i] = 1;
                else decomp[i] = 0;
            for(int i=0;i<n;i++){
                if(symmetry.count(remain[i])) continue;
                temp = remain[i];
                bool isSymmetric = true;
                for(int j=0;j<4;j++,temp/=10)
                    if(decomp[j]!=clr.count(temp%10)){
                        isSymmetric = false;
                        break;
                    }
                if(isSymmetric)symmetry.insert(remain[i]);
            }
        } else symmetry.insert(remain[cnt]);
    }
    int miniIdx = 0;
    int mini = 1e5;
    for(int cnt=1;cnt<n;cnt++)
        if(etps[cnt]<mini && symmetry.count(remain[cnt]))
            miniIdx=cnt;
    return arr[miniIdx];
}


int main(){
    srand(time(NULL));
    vector<int> remain;
    for(int cnt=1;cnt<10000;cnt++){
        int temp = cnt;
        bool pos=true;
        bool dig[10] = {};
        for(int d=0;d<4;d++)
            if(dig[temp%10]){
                pos = false;
                break;
            } else{
                dig[temp%10] = true;
                temp/=10;
            }
        if(pos) remain.push_back(cnt);
    }

    vector<int> pick(remain.begin(),remain.end());
    int testTimes = pick.size();
    double avg = 0;
    for(int t=0;t<testTimes;t++){
        vector<int> remainDuplicate=remain;
        #define remain remainDuplicate
        int ans = pick[t];
        bool getit = false;
        int time=0;
        while(remain.size()>1){
            time++;
            int guess = takeGuess(remain,time);
            printf("Guess: %04d\n",guess);
            int a,b;
            /// Auto Process
            pair<int,int> autoAB = countAB(ans,guess);
            a = autoAB.first; b = autoAB.second;
            //cin>>a>>b;
            if(a==4) getit=true;
            trim(remain,guess,a,b);
        }
        if(!getit) time++;
        printf("Answer: %04d\n",remain.front());
        avg+=time;
        cout<<time<<" times, current avg: "<<(avg/(t+1))<<"\n";
        #undef remain
    }
    avg/=testTimes;
    cout<<avg<<" times in avg\n";
    return 0;
}
