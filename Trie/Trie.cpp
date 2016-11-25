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
        Node* next[valueRange];
        Node(){
            for(int cnt=0;cnt<=valueRange;cnt++)
                next[cnt]=NULL;
        }
        Node(Ch ch):ch(ch){
            for(int cnt=0;cnt<=valueRange;cnt++)
                next[cnt]=NULL;
        }
    }head;
public:
    Trie():strNum(0),head(){}
    void insert(Container const& str,Val val){
        int top=0;
        ++strNum;
        Node* iter=&head;
        while(top<str.size()){
            if(iter->next[str[top]])
                iter=iter->next[str[top]];
            else
                iter=iter->next[str[top]]=new Node(str[top]);
            top++;
        }
        iter->next[valueRange]=new Val(val);
    }

    Val& operator[](Container const& str){
        int top=0;
        Node* iter=&head;
        while(top<str.size()){
            if(iter->next[str[top]])
                iter=iter->next[str[top]];
            else
                iter=(iter->next[str[top]]=new Node(str[top]));
            top++;

        }
        if(iter->next[valueRange]){
            iter=iter->next[valueRange];
            return *(Val*)iter;
        }
        else{
            ++strNum;
            iter->next[valueRange]=(Node*) new Val;
            iter=iter->next[valueRange];
            return *(Val*)iter;
        }
    }

    int count(Container const& str){
        int top=0;
        Node* iter=&head;
        while(top<str.size()){
            if(iter->next[str[top]])
                iter=iter->next[str[top]];
            else return 0;
            top++;
        }
        return 1;
    }

    inline size_t size(){return strNum;}
};


int main(){
    Trie<string, int> t;
    t["asd"]=2;
    t["asdf"]=3;
    t["sldkjkg"]=5;
    cout<<t["asdf"]<<endl<<t["asd"]<<endl<<t.size()<<endl;;
    return 0;
}
