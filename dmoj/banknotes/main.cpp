#include <iostream>
#define inf 999999999
using namespace std;

int value[200], num[200], N, K, dp[2][20001];

int solve() {
    fill(begin(dp[0]), end(dp[0]), inf);
    fill(begin(dp[1]), end(dp[1]), inf);
    dp[1][0] = 0;

    for (int i = 0; i < N; i++) {
        int ch = i & 1, ph = !ch;
        for (int k = 0; k <= K; k++) {
            dp[ch][k] = dp[ph][k];
            for (int j = 1; j <= num[i] && k >= j * value[i]; j++) {
                dp[ch][k] = min(dp[ch][k], dp[ph][k - j * value[i]] + j);
            }
        }
    }

    return dp[(N - 1) & 1][K];
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", value + i);
    for (int i = 0; i < N; i++) scanf("%d", num + i);
    scanf("%d", &K);
    printf("%d", solve());
    return 0;
}