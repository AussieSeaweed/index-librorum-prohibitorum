#include <iostream>
#include <cstring>

bool exists[60][60];
int R, C, S, B, K, M, T[60][60], V[60][60];
int dp[60][60][60][60];

int solve(int r, int c, int b, int k) {
    if (b >= B) return -2000000000;
    if (r > R + 1) return 0;
    if (~dp[r][c][b][k]) return dp[r][c][b][k];
    if (k == 0) return dp[r][c][b][k] = 0;
    dp[r][c][b][k] = 0;

    for (int nc = std::max(c - M, 1); nc <= std::min(c + M, C); nc++)
        dp[r][c][b][k] = std::max(dp[r][c][b][k],
                std::max(exists[r][c] ? V[r][c] + solve(r + 1, nc, b + T[r][c], k - 1) : 0,
                         solve(r + 1, nc, b, k)));

    return dp[r][c][b][k];
}

int main() {
    scanf("%d%d%d%d%d%d", &R, &C, &S, &B, &K, &M);

    while (S--) {
        int t, v, c, r;
        scanf("%d%d%d%d", &t, &v, &c, &r);
        exists[r][c] = true;
        V[r][c] = v;
        T[r][c] = t;
    }

    memset(dp, -1, sizeof dp);

    printf("%d\n", solve(0, 1, 0, K));
    return 0;
}