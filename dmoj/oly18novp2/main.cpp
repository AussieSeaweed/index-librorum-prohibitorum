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

int N, ids[1000001];
pair<int, int> hw[1000000];
long long ans = 0;

int root(int node) { return node == ids[node] ? node : ids[node] = root(ids[node]); }

int main() {
    for (int i = 1; i <= 1000000; i++) ids[i] = i;
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(hw[i].second);
        scan(hw[i].first);
    }

    sort(hw, hw + N, greater<pair<int, int>>());

    for (int i = 0; i < N; i++) {
        int r = root(hw[i].second);
        if (r) {
            ids[r] = r - 1;
            ans += hw[i].first;
        }
    }

    printf("%lld\n", ans);

    return 0;
}