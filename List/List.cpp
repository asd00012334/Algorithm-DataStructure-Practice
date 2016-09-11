#include <bits/stdc++.h>

using namespace std;

template<typename type>
class List{
    struct Node{
        Node* prev;
        Node* next;
        type val;
        Node():
            prev(NULL), next(NULL){}
        Node(Node* prev, Node* next, type val):
            prev(prev), next(next), val(val){}
        Node(Node* prev, Node* next):
            prev(prev), next(next){}
    }*head, *tail;
    size_t len;
public:
    List():len(0), head(NULL), tail(NULL){}
    ~List(){
        this->clear();
    }
    void push_back(type val){
        if(len==0) head = tail = new Node(NULL,NULL,val);
        else{
            tail->next = new Node(tail,NULL,val);
            tail = tail->next;
        }
        ++len;
    }

    void push_front(type val){
        if(len==0) head = tail = new Node(NULL,NULL,val);
        else{
            head->prev = new Node(NULL,head,val);
            head = head->prev;
        }
        ++len;
    }

    void pop_back(){
        if(len==0) throw exception();
        if(len==1){
            delete tail;
            head = tail = NULL;
        }
        else{
            tail = tail->prev;
            delete tail->next;
            tail->next = NULL;
        }
        --len;
    }

    void pop_front(){
        if(len==0) throw exception();
        if(len==1){
            delete head;
            head = tail = NULL;
        }
        else{
            head = head->next;
            delete head->prev;
            head->prev = NULL;
        }
        --len;
    }

    size_t size(){return len;}

    void clear(){
        while(head){
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = NULL;
        len = 0;
    }

    List& operator=(List& right){
        List& left = *this;
        left.clear();
        Node* nev = right.head;
        while(nev){
            left.push_back(nev->val);
            nev = nev->next;
        }
        return left;
    }

    List& swap(List& That){
        List& This = *this;
        swap(This.head,That.head);
        swap(This.tail,That.tail);
        swap(This.len,That.len);
        return This;
    }

    type& front(){return head->val;}
    type& back() {return tail->val;}

    struct iterator{
        Node* ptr;
        iterator(): ptr(NULL){}
        iterator(Node *ptr): ptr(ptr){}
        iterator(iterator const& input){
            ptr = input.ptr;
        }

        iterator& operator=(iterator const& right){
            iterator& left = *this;
            left.ptr = right.ptr;
            return left;
        }

        type& operator*(){
            if(ptr==NULL) throw exception();
            return ptr->val;
        }

        iterator& operator++(){
            if(ptr==NULL) throw exception();
            ptr = ptr->next;
            return *this;
        }

        iterator operator++(int){
            if(ptr==NULL) throw exception();
            iterator output(ptr);
            ptr = ptr->next;
            return output;
        }

        iterator& operator--(){
            if(ptr==NULL) throw exception();
            ptr = ptr->prev;
            return *this;
        }

        iterator operator--(int){
            if(ptr==NULL) throw exception();
            iterator output(ptr);
            ptr = ptr->prev;
            return output;
        }

        friend bool operator==(iterator const& left, iterator const& right){
            return left.ptr==right.ptr;
        }

        friend bool operator!=(iterator const& left, iterator const& right){
            return left.ptr!=right.ptr;
        }

    };

    struct reverse_iterator{
        Node* ptr;
        reverse_iterator(): ptr(NULL){}
        reverse_iterator(Node *ptr): ptr(ptr){}
        reverse_iterator(reverse_iterator const& input){
            ptr = input.ptr;
        }

        reverse_iterator& operator=(reverse_iterator const& right){
            reverse_iterator& left = *this;
            left.ptr = right.ptr;
            return left;
        }

        type& operator*(){
            if(ptr==NULL) throw exception();
            return ptr->val;
        }

        reverse_iterator& operator++(){
            if(ptr==NULL) throw exception();
            ptr = ptr->next;
            return *this;
        }

        reverse_iterator operator++(int){
            if(ptr==NULL) throw exception();
            reverse_iterator output(ptr);
            ptr = ptr->next;
            return output;
        }

        reverse_iterator& operator--(){
            if(ptr==NULL) throw exception();
            ptr = ptr->prev;
            return *this;
        }

        reverse_iterator operator--(int){
            if(ptr==NULL) throw exception();
            reverse_iterator output(ptr);
            ptr = ptr->prev;
            return output;
        }

        friend bool operator==(reverse_iterator const& left, reverse_iterator const& right){
            return left.ptr==right.ptr;
        }

        friend bool operator!=(reverse_iterator const& left, reverse_iterator const& right){
            return left.ptr!=right.ptr;
        }

    };

    iterator begin(){
        return iterator(head);
    }
    iterator end(){
        return iterator(NULL);
    }

    reverse_iterator rbegin(){
        return reverse_iterator(tail);
    }
    reverse_iterator rend(){
        return reverse_iterator(NULL);
    }

};


int main(){

    List<int> lis;
    for(int cnt=0;cnt<20;cnt++)
        lis.push_back(cnt);
    List<int>::iterator i;
    for(i=lis.begin();i!=lis.end();++i)
        printf("%d ",*i);
    printf("\n");

    return 0;
}
