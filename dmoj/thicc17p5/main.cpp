#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, K, ind[1000001];
bool used[1000001];
long long ans = 0;
set<int> indices;

int main() {
    scan(N);
    scan(K);

    for (int i = 0; i < N; i++) {
        int a;
        scan(a);

        if (used[a])
            indices.erase(ind[a]);

        used[a] = true;
        ind[a] = i;
        indices.insert(i);

        if (indices.size() > K) indices.erase(indices.begin());
        if (indices.size() == K) ans += *indices.begin() + 1;
    }

    printf("%lld\n", ans);

    return 0;
}