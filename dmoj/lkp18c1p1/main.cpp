#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, K, a[10], ans = 0;

int main() {
    scan(N);
    scan(K);
    for (int i = 0; i < N; i++)
        scan(a[i]);
    for (int i = N - 1; i >= 0; i--) {
        if (K >= a[i]) {
            ans += K / a[i];
            K = K % a[i];
        }
    }
    if (K) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
    return 0;
}