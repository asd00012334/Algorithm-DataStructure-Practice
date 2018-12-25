#include<bits/stdc++.h>

using namespace std;

/// Remark.
/// This code is not completed and verified at all!!!

#define pt complex<double>
#define X real()
#define Y imag()

inline double area(pt a, pt b, pt c){
    cout <<arg((b-a)/(c-a)) <<"\n";
    auto &&x = b-a, &&y = c-a;
    return abs(x)*abs(y)*sin(arg(x/y))/2;
}

#define pr pair<pt,pt>
#define A first
#define B second

bool inter(pr l1, pr l2){
    function<bool(pr, pt, pt)> diff = [&](pr l, pt a, pt b){
        pt&& d = l.B-l.A;
        return arg((a-l.A)/d)*arg((b-l.A)/d)<0;
    };
    return diff(l1,l2.A,l2.B) && diff(l2,l1.A,l1.B);
}

int main(){


}
