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

long long N, a[100000], b[100000], dp[100001][3];

long long solve(int i, int consec) {
    if (consec == 3) return -INF;
    if (~dp[i][consec]) return dp[i][consec];
    if (i == N) return dp[i][consec] = 0;
    return dp[i][consec] = max(a[i] + solve(i + 1, consec + 1), b[i] + solve(i + 1, 0));
}

int main() {
    scan(N);
    for (int i = 0; i < N; i++)
        scanf("%lld", a + i);
    for (int i = 0; i < N; i++)
        scanf("%lld", b + i);
    memset(dp, -1, sizeof dp);
    printf("%lld\n", solve(0, 0));
    return 0;
}