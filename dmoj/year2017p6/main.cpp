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

int N, c[5001], d[5001];
long long dp[5000][5000];

long long solve() {
    for (int i = 0; i < N; i++) dp[i][N - 1] = 0;

    for (int i = N - 2; i >= 0; i--) {
        dp[i][i] = c[i] + dp[i + 1][min(N - 1, i + d[i])];
        for (int j = i + 1; j <= N - 1; j++) {
            dp[i][j] = min(dp[i + 1][j], c[i] + dp[i + 1][min(N - 1, j + d[i])]);
        }
    }

    return dp[0][0];
}

int main() {
    pscan(N);

    for (int i = 0; i < N; i++) {
        pscan(c[i]);
        pscan(d[i]);
    }

    printf("%lld\n", solve());
    return 0;
}