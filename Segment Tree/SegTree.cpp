#include <bits/stdc++.h>

using namespace std;

template<typename type>
class SegTree{
    static type const& (*operate)(type const&,type const&);
    int rootIdx;
    size_t length;
    struct Node{
        type val;
        int idx;
        int begin;
        int end;
        int left;
        int right;
        Node(){}
        Node(type val, int idx):
            val(val),idx(idx){}
    };
    vector<Node> storage;
public:
    SegTree(){
        length = 0;
        rootIdx = EOF;
        operate = NULL;
    }

    template<typename iter>
    SegTree(iter begin, iter end, type const& (*operate)(type const&,type const&) = max){
        build(begin,end, operate);
    }

    size_t const& size(){return length;}

    void clear(){
        length = 0;
        storage.clear();
        rootIdx = EOF;
        operate = NULL;
    }

    template<typename iter>
    Node build(iter begin, iter end, type const& (*operate)(type const&,type const&) = max, iter initial = (iter)NULL){
        if(initial==(iter)NULL){
            storage.clear();
            initial = begin;
            SegTree::operate = operate;
            length=0;
        }
        int size = end-begin;
        if(size == 1){
            length++;
            storage.push_back(Node(*begin,storage.size()));
            storage.back().begin = begin - initial;
            storage.back().end = end - initial;
            storage.back().left = storage.back().right = EOF;
            rootIdx = storage.back().idx;
            return storage.back();
        }
        Node left = build(begin, begin+size/2,operate,initial);
        Node right = build(begin+size/2,end,operate,initial);
        storage.push_back(Node(operate(left.val,right.val),storage.size()));
        storage.back().begin = begin - initial;
        storage.back().end = end - initial;
        storage.back().left = left.idx;
        storage.back().right = right.idx;
        rootIdx = storage.back().idx;
        return storage.back();
    }

    type query(int begin ,int end, int curIdx = EOF){
        if(curIdx == EOF) curIdx = rootIdx;
        Node& cur = storage[curIdx];
        int size = cur.end - cur.begin;
        if(size<0) throw exception();
        if(size==0) return type();
        if(begin<cur.begin||cur.end<end) throw exception();
        if(cur.begin == begin && cur.end == end) return cur.val;
        if(end<=cur.begin+size/2) return query(begin,end,cur.left);///left
        if(cur.begin+size/2<=begin) return query(begin,end,cur.right);///right
        return operate(
                   query(begin,storage[cur.left].end,cur.left),
                   query(storage[cur.right].begin,end,cur.right)
                   );
    }

    void update(int begin, int end, type val, int curIdx = EOF){
        if(curIdx == EOF) curIdx = rootIdx;
        Node& cur = storage[curIdx];
        int size = cur.end - cur.begin;
        if(size<0) throw exception();
        if(size==0) return;
        if(begin<cur.begin||cur.end<end) throw exception();
        if(size==1){
            cur.val = val;
            return;
        }
        if(end<=cur.begin+size/2)
            update(begin,end,val,cur.left);
        else if(cur.begin+size/2<=begin)
            update(begin,end,val,cur.right);
        else{
            update(begin,storage[cur.left].end,val,cur.left);
            update(storage[cur.right].begin,end,val,cur.right);
        }
        cur.val = operate(storage[cur.left].val,storage[cur.right].val);
    }

};

template<typename type>
type const& (*SegTree<type>::operate)(type const&,type const&);

int main(){
    string str = "This is a segment tree.";
    SegTree<char> seg;
    seg.build(str.begin(),str.end());
    for(int cnt=0;cnt<seg.size();cnt++)
        cout<<seg.query(cnt,cnt+1);
    cout<<endl;
    return 0;
}
