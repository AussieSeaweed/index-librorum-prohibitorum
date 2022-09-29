#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int G, P;
int ids[100001];
int root(int node) { return node == ids[node] ? node : ids[node] = root(ids[node]); }

int main() {
    scan(G);
    for (int i = 1; i <= G; i++) ids[i] = i;
    scan(P);
    int p;

    for (p = 1; p <= P; p++) {
        int g;
        scan(g);
        int r = root(g);
        if (r) {
            ids[r] = root(r - 1);
        } else {
            printf("%d\n", p - 1);
            break;
        }
    }

    if (p == P + 1) printf("%d\n", P);

    return 0;
}