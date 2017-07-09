#include<bits/stdc++.h>

using namespace std;

struct Node{
    int val;
    int sum;
    bool tag;
    int size;

    int key;
    int pri;
    Node *left, *right;
    Node(): tag(false), left(NULL), right(NULL), pri(rand()){}
    Node(int key, int val=0):
        tag(false),
        size(1),
        key(key),
        sum(val),
        val(val),
        pri(rand()),
        left(NULL),
        right(NULL)
        {}
};
inline int getSum(Node* nd){return nd?nd->sum:0;}
inline int getSize(Node* nd){return nd?nd->size:0;}
inline void pull(Node* nd){
    if(!nd) return;
    nd->sum = getSum(nd->left)+getSum(nd->right)+nd->val;
    nd->size = getSize(nd->left)+getSize(nd->right)+1;
}
inline void push(Node* nd){
    nd->tag = false;
    if(nd->left){
        nd->left->tag = true;
        nd->left->val = nd->val;
        nd->left->sum = nd->left->val * nd->left->size;
    }
    if(nd->right){
        nd->right->tag = true;
        nd->right->val = nd->val;
        nd->right->sum = nd->right->val * nd->right->size;
    }
}
Node* merge(Node* left, Node* right){
    if(!left || !right) return left?left:right;
    if(left->pri>right->pri){
        if(left->tag) push(left);
        left->right = merge(left->right,right);
        pull(left);
        return left;
    } else{
        if(right->tag) push(right);
        right->left = merge(left,right->left);
        pull(right);
        return right;
    }
}
pair<Node*, Node*> split(Node* nd, int key){
    if(!nd) return pair<Node*,Node*>(NULL,NULL);
    if(nd->tag) push(nd);
    if(nd->key<key){
        auto temp = split(nd->right,key);
        nd->right = temp.first;
        pull(nd);
        return pair<Node*, Node*>(nd, temp.second);
    } else{
        auto temp = split(nd->left, key);
        nd->left = temp.second;
        pull(nd);
        return pair<Node*, Node*>(temp.first, nd);
    }
}
template<class iter>
Node* build(iter begin, iter end){
    srand(time(NULL));
    int size = end-begin;
    Node* root = NULL;
    for(int cnt=0;cnt<size;cnt++)
        root = merge(root,new Node(cnt,begin[cnt]));
    return root;
}
int query(Node *&root,int begin, int end){
    auto temp = split(root, end);
    root = temp.second;
    temp = split(temp.first,begin);
    swap(temp.second,root);
    int sum = getSum(root);
    root = merge(root,temp.second);
    root = merge(temp.first,root);
    return sum;
}

void update(Node *&root, int begin, int end, int val){
    auto temp = split(root, end);
    root = temp.second;
    temp = split(temp.first,begin);
    swap(temp.second,root);
    root->tag = true;
    root->val = val;
    root->sum = val*root->size;
    root = merge(root,temp.second);
    root = merge(temp.first,root);
}

int main(){
    vector<int> arr{10,20,30,40,5,6,7,4,8};
    Node *root = build(arr.begin(),arr.end());
    update(root,1,3,20);
    printf("%d\n",query(root,0,3));
}
