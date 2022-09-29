#include <stdio.h>

int dp[100001][16];
int pt[100000][4];
int N;

int solve() {
    for (int i = 0; i < 16; i++) dp[N][i] = 0;
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < 16; j++) {
            dp[i][j] = dp[i + 1][j];
            for (int k = 0; k < 4; k++)
                if (j & (1 << k) && pt[i][k] != -1)
                    if (dp[i][j] < pt[i][k] + dp[i + 1][j - (1 << k)])
                        dp[i][j] = pt[i][k] + dp[i + 1][j - (1 << k)];
        }
    }
    return dp[0][15];
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) for (int j = 0; j < 4; j++) scanf("%d", &pt[i][j]);
    printf("%d", solve());
    return 0;
}