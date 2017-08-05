#include <bits/stdc++.h>

using namespace std;

template<int base, int expo>
struct Pow{
    static const int value=expo%2?
        base*Pow<base,expo-1>::value:
        Pow<base,expo/2>::value*Pow<base,expo/2>::value;
};

template<int base>
struct Pow<base,0>{
    static const int value=1;
};

template<typename Container=string, typename Val=int>
class Trie{
    typedef typename Container::value_type Ch;
    static const int charSize=sizeof(Ch)*8;
    static const int valueRange=Pow<2,charSize>::value;
    size_t strNum;
    struct Node{
        Ch ch;
        bitset<valueRange+1> nxtValid;
        Node* next[valueRange+1];
        Node* trace;
        Node():trace(NULL){}
        Node(Ch ch, Node* trace=NULL):ch(ch),trace(trace){}
    }head;
public:
    Trie():strNum(0),head(){}
    void insert(Container const& str,Val val){
        int top=0;
        ++strNum;
        Node* iter=&head;
        while(top<str.size()){
            if(iter->nxtValid[iter->next[str[top]]])
                iter=iter->next[str[top]];
            else{
                Node* trace = iter->trace;
                while(trace){
                    if(trace->nxtValid[str[top]]) break;
                    trace = trace->nxtValid;
                }
                iter->nxtValid[iter->next[str[top]]]=1;
                iter=iter->next[str[top]]=new Node(str[top],trace);
            }
            top++;
        }
        iter->nxtValid[iter->next[valueRange]]=1;
        iter->next[valueRange]=new Val(val);
    }

    Val& operator[](Container const& str){
        int top=0;
        Node* iter=&head;
        while(top<str.size()){
            if(iter->nxtValid[str[top]])
                iter=iter->next[str[top]];
            else{
                iter->nxtValid[str[top]]=1;
                iter=(iter->next[str[top]]=new Node(str[top]));
            }
            top++;

        }
        if(iter->nxtValid[valueRange]){
            iter=iter->next[valueRange];
            return *(Val*)iter;
        }
        else{
            ++strNum;
            iter->nxtValid[valueRange]=1;
            iter->next[valueRange]=(Node*) new Val;
            iter=iter->next[valueRange];
            return *(Val*)iter;
        }
    }

    int count(Container const& str){
        int top=0;
        Node* iter=&head;
        while(top<str.size()){
            if(iter->nxtValid[str[top]])
                iter=iter->next[str[top]];
            else return 0;
            top++;
        }
        return 1;
    }

    inline size_t size(){return strNum;}

    void match(Container const& str, vector<int>& pos){
        Node* iter = &head;
        if(iter->nxtValid[valueRange])
            pos.push_back(str.size()-1);
        for(int cnt=0;cnt<str.size();cnt++){
            if(iter->nxtValid[str[cnt]]){
                iter = iter->next[str[cnt]];
            } else{
                iter = iter->trace?iter->trace:&head;
                cnt--;
            }
            if(iter->nxtValid[valueRange])
                pos.push_back(cnt);
        }
    }

};


int main(){
    Trie<string, int> t;
    t["asd"]=2;
    t["asdf"]=3;
    t["sldkjkg"]=5;
    cout<<t["asdf"]<<endl<<t["asd"]<<endl<<t.size()<<endl;
    vector<int> pos;
    t.match("asdfasdfaaaaasdf",pos);
    for(int cnt=0;cnt<pos.size();cnt++)
        printf("%d;\n",pos[cnt]);
    return 0;
}
