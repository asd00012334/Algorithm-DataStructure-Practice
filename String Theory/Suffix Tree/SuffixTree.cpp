#include<bits/stdc++.h>

using namespace std;

class SuffixTree{
    struct Node{
        bool tail;
        Node *prev, *back, *nxt[127];
        Node(): back(this),prev(NULL),nxt{},tail(true){}
        Node(Node* prev): back(this),prev(prev),nxt{},tail(true){}
    } *head;
    queue<Node*> leaf;
    void push(char c){
        int n=leaf.size();
        while(n--){
            Node* newNd;
            leaf.front()->tail = false;
            if(leaf.front()->nxt[c]){
                newNd = leaf.front()->nxt[c];
                leaf.front()->nxt[c]->tail = true;
            } else{
                newNd = leaf.front()->nxt[c] = new Node(leaf.front());
                Node* pivot = leaf.front()->back;
                while(pivot->back!=pivot && !pivot->nxt[c]) pivot=pivot->back;
                if(pivot->nxt[c]) newNd->back=pivot->nxt[c];
                else newNd->back=pivot;
            }
            leaf.push(newNd); leaf.pop();
        }
        head->tail = true; leaf.push(head);
    }

public:
    SuffixTree(string const& str): head(new Node()){
        leaf.push(head);
        for(int cnt=0;cnt<str.size();++cnt)
            push(str[cnt]);
    }
    bool matchInfix(string const& str){
        Node* pivot = head;
        for(int cnt=0;cnt<str.size();++cnt)
            if(pivot->nxt[str[cnt]]) pivot=pivot->nxt[str[cnt]];
            else return false;
        return true;
    }
    void dump(vector<char>& prefix,Node* rt=NULL){
        if(!rt) rt=head;
        for(int cnt=0;cnt<127;++cnt)
            if(rt->nxt[cnt]){
                prefix.push_back(cnt);
                dump(prefix,rt->nxt[cnt]);
                prefix.pop_back();
            }
        if(rt->tail){
            for(int cnt=0;cnt<prefix.size();++cnt)
                cout<<prefix[cnt];
            cout<<"\n";
        }
    }

};

int main(){
    SuffixTree a("HelloWorld");
    a.dump(*new vector<char>());
    cout<< a.matchInfix("lloW") <<"\n";

    return 0;
}
