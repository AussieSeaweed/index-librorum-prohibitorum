#include <iostream>
#include <cstring>

#define inf 2000000000

int dp[151][301][101], M, U, R, V[150], T[150], F[150];

int solve(int r, int m, int u) {
    if (m < 0) return -inf;
    if (u < 0) return -inf;
    if (~dp[r][m][u]) return dp[r][m][u];
    if (r == R) return dp[r][m][u] = 0;

    return dp[r][m][u] = std::max(solve(r + 1, m, u), V[r] + solve(r + 1, m - T[r], u - F[r]));
}

int main() {
    scanf("%d%d%d", &M, &U, &R);

    for (int i = 0; i < R; i++)
        scanf("%d%d%d", V + i, T + i, F + i);

    memset(dp, -1, sizeof dp);
    printf("%d\n", solve(0, M, U));

    return 0;
}