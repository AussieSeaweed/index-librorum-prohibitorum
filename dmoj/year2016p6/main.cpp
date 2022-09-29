#include <iostream>
#include <cstring>
#define inf 99999999
using namespace std;

int dp[2][1 << 10][1 << 10], L, R, W, lw[10], rw[10];

bool invalid(int lb, int rb) {
    int ls = 0, rs = 0;

    for (int i = 0; i < L; i++)
        if (lb & (1 << i))
            ls += lw[i];

    for (int i = 0; i < R; i++)
        if (rb & (1 << i))
            rs += rw[i];

    return abs(ls - rs) > W;
}

int solve(int side, int lb, int rb) {
    if (dp[side][lb][rb] != -1) return dp[side][lb][rb];
    if (!lb && !rb)
        return dp[side][lb][rb] = 0;
    if (invalid(lb, rb)) return dp[side][lb][rb] = inf;
    dp[side][lb][rb] = inf;

    if (side == 0) {
        for (int i = 0; i < L; i++) {
            if (lb & (1 << i)) {
                dp[side][lb][rb] = min(dp[side][lb][rb], min(solve(0, lb - (1 << i), rb), 1 + solve(1, lb - (1 << i), rb)));
            }
        }
    } else {
        for (int i = 0; i < R; i++) {
            if (rb & (1 << i)) {
                dp[side][lb][rb] = min(dp[side][lb][rb], min(1 + solve(0, lb, rb - (1 << i)), solve(1, lb , rb - (1 << i))));
            }
        }
    }

    return dp[side][lb][rb];
}

int main() {
    scanf("%d%d%d", &L, &R, &W);

    for (int i = 0; i < L; i++) scanf("%d", lw + i);
    for (int i = 0; i < R; i++) scanf("%d", rw + i);

    memset(dp, -1, sizeof dp);

    printf("%d", 1 + solve(0, (1 << L) - 1, (1 << R) - 1));
    return 0;
}