#include <iostream>
#include <cstring>

#define inf 999999999999999999

int N, M;
long long raisins[51][51];
long long dp[51][51][51][51];

long long get_sum(int i1, int j1, int i2, int j2) {
    return raisins[i2][j2] + raisins[i1 - 1][j1 - 1] - raisins[i1 - 1][j2] - raisins[i2][j1 - 1];
}

long long solve(int i1, int j1, int i2, int j2) {
    if (~dp[i1][j1][i2][j2]) return dp[i1][j1][i2][j2];
    if (i1 == i2 && j1 == j2) return dp[i1][j1][i2][j2] = 0;
    dp[i1][j1][i2][j2] = inf;
    long long sum = get_sum(i1, j1, i2, j2);

    for (int i = i1; i < i2; i++) {
        dp[i1][j1][i2][j2] = std::min(dp[i1][j1][i2][j2], sum + solve(i1, j1, i, j2) + solve(i + 1, j1, i2, j2));
    }

    for (int j = j1; j < j2; j++) {
        dp[i1][j1][i2][j2] = std::min(dp[i1][j1][i2][j2], sum + solve(i1, j1, i2, j) + solve(i1, j + 1, i2, j2));
    }

    return dp[i1][j1][i2][j2];
}

int main() {
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) {
            scanf("%lld", &raisins[i][j]);
            raisins[i][j] += raisins[i - 1][j] + raisins[i][j - 1] - raisins[i - 1][j - 1];
        }

    memset(dp, -1, sizeof dp);
    printf("%lld\n", solve(1, 1, N, M));
    return 0;
}