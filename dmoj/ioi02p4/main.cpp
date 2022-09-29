#include <iostream>
using namespace std;
#define inf 2000000000

int dp[10002], T[10002], F[10002], N, S;

int main() {
    scanf("%d%d", &N, &S);

    for (int i = 1; i <= N; i++) {
        scanf("%d%d", T + i, F + i);
        T[i] += T[i - 1];
        F[i] += F[i - 1];
    }

    int pred = N + 1;

    for (int i = N; i >= 1; i--) {
        dp[i] = inf;
        for (int j = pred; j > i; j--) {
            int cur = dp[j] + (T[j - 1] - T[i - 1] + S) * (F[N] - F[i - 1]);
            if (cur <= dp[i]) {
                dp[i] = cur;
                pred = j;
            }
        }
    }

    printf("%d", dp[1]);

    return 0;
}