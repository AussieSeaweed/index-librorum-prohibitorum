#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N;
long long values[1000000], dp[2][1000001];

inline long long solve() {
    for (int i = N - 1; i >= 0; i--) {
        dp[0][i] = max(dp[0][i + 1], dp[1][i + 1]);
        dp[1][i] = values[i] + dp[0][i + 1];
    }

    return max(dp[0][0], dp[1][0]);
}

int main() {
    scan(N);
    for (int i = 0; i < N; i++) scanf("%lld", values + i);
    printf("%lld\n", solve());
    return 0;
}