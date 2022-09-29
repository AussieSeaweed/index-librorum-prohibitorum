#include <iostream>
#define inf 2000000000

int target, N, t[15], dp[2][1 << 15];

int solve(bool front, int bitmask) {
    if (dp[front][bitmask] != -1) return dp[front][bitmask];
    if (bitmask == target) return dp[front][bitmask] = 0;
    dp[front][bitmask] = inf;

    if (front) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (!(bitmask & (1 << i)) && !(bitmask & (1 << j))) {
                    dp[front][bitmask] = std::min(dp[front][bitmask],
                            std::max(t[i], t[j]) + solve(false, bitmask + (1 << i) + (1 << j)));
                }
            }
        }
    } else {
        for (int i = 0; i < N; i++) {
            if (bitmask & (1 << i)) {
                dp[front][bitmask] = std::min(dp[front][bitmask], t[i] + solve(true, bitmask - (1 << i)));
            }
        }
    }

    return dp[front][bitmask];
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", t + i);
    target = (1 << N) - 1;
    std::fill(std::begin(dp[0]), std::end(dp[0]), -1);
    std::fill(std::begin(dp[1]), std::end(dp[1]), -1);
    printf("%d", solve(true, 0));
    return 0;
}