#include <iostream>
#define inf 999999999
using namespace std;

int difficulty[3][150000];
int dp[150001][1 << 3][3];
int N;

int solve() {
    for (int i = 0; i < 3; i++) dp[N][0][i] = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 1; j < 8; j++) dp[N][j][i] = inf;
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 3; k++) {
                if (!(j & (1 << k))) {
                    dp[i][j][k] = difficulty[k][i] + dp[i + 1][j][k];
                    if (i)
                        for (int l = 0; l < 3; l++) {
                            if (j & (1 << l)) {
                                dp[i][j][k] = min(dp[i][j][k], difficulty[l][i] + dp[i + 1][j - (1 << l)][l]);
                            }
                        }
                } else {
                    dp[i][j][k] = inf;
                }
            }
        }
    }

    return min(
            min(
                    dp[0][7 - (1 << 0)][0],
                    dp[0][7 - (1 << 1)][1]
                    ),
            dp[0][7 - (1 << 2)][2]
            );
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &difficulty[i][j]);
        }
    }
    printf("%d", solve());
    return 0;
}