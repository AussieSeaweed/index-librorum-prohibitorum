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

long long N, H, dp[2][5001][2], g[5000], h[5000], q[5000], t[5000];

long long solve() {
    for (int i = N - 1, a = (N - 1) & 1, b = !a; i >= 0; i--, a = !a, b = !b) {
        for (int time = 0; time < t[i]; time++) {
            dp[a][time][1] = dp[b][time][0];
        }
        for (int time = t[i]; time <= H; time++) {
            dp[a][time][1] = max(dp[b][time][0], q[i] + dp[a][time - t[i]][1]);
        }
        for (int time = 0; time < h[i]; time++) {
            dp[a][time][0] = dp[b][time][0];
        }
        for (int time = h[i]; time <= H; time++) {
            dp[a][time][0] = max(dp[b][time][0], g[i] + dp[a][time - h[i]][1]);
        }
    }

    return dp[0][H][0];
}

int main() {
    scan(N);
    scan(H);

    for (int i = 0; i < N; i++) {
        scan(g[i]);
        scan(h[i]);
        scan(q[i]);
        scan(t[i]);
    }

    printf("%lld\n", solve());

    return 0;
}