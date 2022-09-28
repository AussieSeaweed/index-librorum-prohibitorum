#include <iostream>
#define inf 9000000000000000000

int N, M, k[1002][1002];
long long split[1002], dp[1002][1002];

int main() {
    while (std::cin >> N >> M) {
        for (int i = 1; i <= M; i++) std::cin >> split[i];
        split[M + 1] = N;

        for (int i = 2; i <= M + 1; i++) dp[i - 1][i] = split[i] - split[i - 2], k[i - 1][i] = i;

        for (int dist = 2; dist <= M; dist++) {
            for (int i = 1; i <= M + 1 - dist; i++) {
                int j = dist + i;
                dp[i][j] = inf;
                for (int m = k[i][j - 1]; m <= k[i + 1][j]; m++) {
                    long long cur = dp[i][m - 1] + dp[m][j] + split[j] - split[i - 1];
                    if (cur < dp[i][j]) {
                        dp[i][j] = cur;
                        k[i][j] = m;
                    }
                }
            }
        }
        printf("%lld\n", dp[1][M + 1]);
    }
    return 0;
}