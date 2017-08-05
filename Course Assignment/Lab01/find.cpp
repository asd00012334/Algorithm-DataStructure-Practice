#include <iostream>
#include <fstream>
#include <time.h>
#include "String.hpp"
#include "List.hpp"
using namespace std;

inline char toLower(char ch){return 'A'<=ch&&ch<='Z'?(ch-'A'+'a'):ch;}

void findAllKMP(String const& str, List<String>& patList, int times){
    static int init=0;
    static List<int*> prefixList;
    static List<int> matched;
    if(!init){ // Build prefix array for each pattern
        for(List<String>::iterator iter=patList.begin();iter!=patList.end();++iter){
            prefixList.push_back(new int[iter->size()]);
            matched.push_back(0);
            int* prefix = prefixList.back();
            int pat=1;
            int size = iter->size();
            prefix[0]=0;
            while(pat<size){
                int pre=prefix[pat-1];
                while(pre>0&&toLower((*iter)[pre])!=toLower((*iter)[pat]))
                    pre = prefix[pre-1];
                prefix[pat]=pre;
                if(toLower((*iter)[pre])==toLower((*iter)[pat]))
                    prefix[pat]++;
                pat++;
            }
        }
        init=1;
    }
    int txt=0;
    while(txt<str.size()){ ///KMP
        List<int>::iterator mIter=matched.begin();
        List<int*>::iterator preIter=prefixList.begin();
        for(List<String>::iterator iter=patList.begin();iter!=patList.end();++iter,++mIter,++preIter){
            /// Enumerate each pattern once and compare it with text
            /// if character match, pattern matched progress incremented
            /// if pattern fully matched, output in the specified form
            /// if character mismatch or pattern fully matched,
            /// back track the pattern matched progress according to prefix array
            /// if all pattern enumerated, text matching progress incremented
            /// if text matching fully completed, break out of the function
            /// go back to first step and loop
            bool hold=true;
            while(hold){
                int& pat = *mIter;
                int* prefix = *preIter;
                if(toLower(str[txt])==toLower((*iter)[pat])){
                    pat++;
                    hold=false;
                }
                else{
                    if(pat) pat=prefix[pat-1];
                    else hold=false;
                }
                if(pat==(*iter).size()){
                    printf("%d %d ",times,txt-pat+1+1);
                    cout<<"\""<<(*iter)<<"\" \""<<str<<"\"\n";
                    if(pat) pat=prefix[pat-1];
                    else hold=false;
                }
            }
        }
        txt++;
    }
}

int main(int argc, char* argv[]){
    if(argc<3) return 1;
    List<String> patList;
    int patSize=0;
    ifstream fpat, ftxt;
    fpat.open(argv[1],ios::in);
    ftxt.open(argv[2],ios::in);
    String txt, pat;
    clock_t clk;
    clk=clock();
    while(!fpat.eof()){
        patList.push_back(String());
        if(getline(fpat,patList.back())==EOF)
            patList.pop_back();
    }
    fpat.close();
    for(int times=1;;times++){
        if(getline(ftxt,txt)==EOF) break;
        findAllKMP(txt, patList, times);
    }
    cout<<clock()-clk<<"ms\n";
    ftxt.close();
    return 0;
}
