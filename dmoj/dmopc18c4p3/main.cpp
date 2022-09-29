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

int N, dp[2][200001], a[200001], b[200001];

int solve(int parity, int i) {
    if (~dp[parity][i]) return dp[parity][i];
    if (i == N) return dp[parity][i] = parity ? inf : 0;

    dp[parity][i] = min(b[i] + solve(!parity, i + 1), a[i] + solve(parity, i + 1));

    return dp[parity][i];
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++)
        scan(a[i]);
    for (int i = 0; i < N; i++)
        scan(b[i]);

    memset(dp, -1, sizeof dp);
    printf("%d\n", solve(0, 0));

    return 0;
}