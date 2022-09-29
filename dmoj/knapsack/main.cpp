#include <iostream>
#define inf 9000000000000000000
using namespace std;

int N, M, capacity[5000], cost[5000];
long long number[5000], profit[5000], volume[5000], dp[2][5001];

void solve() {
    for (int n = 0; n < N; n++) {
        int h = n & 1, ph = !h;

        for (long long i = 0; i <= 5000; i++) {
            dp[h][i] = dp[ph][i];
            for (long long j = 1; j <= number[n] && volume[n] * j <= i; j++) {
                dp[h][i] = max(dp[h][i], dp[ph][i - j * volume[n]] + profit[n] * j);
            }
        }
    }
}

long long solve(int m) {
    return dp[(N - 1) & 1][capacity[m]] - cost[m];
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%lld%lld%lld", number + i, volume + i, profit + i);
    for (int i = 0; i < M; i++)
        scanf("%d%d", capacity + i, cost + i);

    solve();
    long long ans = -inf;

    for (int i = 0; i < M; i++) {
        ans = max(ans, solve(i));
    }

    printf("%lld", ans);

    return 0;
}