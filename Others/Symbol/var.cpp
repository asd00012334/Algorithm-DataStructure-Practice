#include<bits/stdc++.h>

using namespace std;

template<typename type=double>
class var{
    type cache;
    enum VarType{val,add,sub,mul,div} varType;
    vector<var*> child;

    type load(set<var*>& valid){
        if(valid.count(this)) return cache;
        valid.insert(this);
        switch(varType){
        case val: return cache;
        case add: return cache = child[0]->load(valid)+ child[1]->load(valid);
        case sub: return cache = child[0]->load(valid)- child[1]->load(valid);
        case mul: return cache = child[0]->load(valid)* child[1]->load(valid);
        case div: return cache = child[0]->load(valid)/ child[1]->load(valid);
        default: throw exception();
        }
    }

    void biOpSet(var& l, var& r, VarType opType){
        child={&l,&r};
        varType=opType;
    }
public:
    var(): cache(0),varType(val),child{}{}
    var(type const& in): cache(in),varType(val),child{}{}
    var(var const& in): cache(in.cache),varType(in.varType),child(in.child){}
    inline type operator()(){
        set<var*> valid;
        return load(valid);
    }
    friend var& operator+(var& l, var& r){
        var& out = *new var();
        out.biOpSet(l,r,add);
        return out;
    }
    friend var& operator-(var& l, var& r){
        var& out = *new var();
        out.biOpSet(l,r,sub);
        return out;
    }
    friend var& operator*(var& l, var& r){
        var& out = *new var();
        out.biOpSet(l,r,mul);
        return out;
    }
    friend var& operator/(var& l, var& r){
        var& out = *new var();
        out.biOpSet(l,r,div);
        return out;
    }
    var& diff(var& x){
        static var one(1), zero(0);
        switch(varType){
        case val: return this==&x?one:zero;
        case add: return child[0]->diff(x) + child[1]->diff(x);
        case sub: return child[0]->diff(x) - child[1]->diff(x);
        case mul: return (child[0]->diff(x))* *child[1] + *child[0]* child[1]->diff(x);
        case div: return (child[0]->diff(x)* *child[1] - *child[0]* child[1]->diff(x))/(*child[1]* *child[1]);
        default: throw exception();
        }
    }


};

int main(){
    var<double> a(2),b(2);
    var<double> c=a*a+a;
    cout<<(c/a).diff(a)()<<"\n";
    cout<<(a+a).diff(a)()<<"\n";
    cout<<c.diff(a)()<<"\n";
    return 0;
}
