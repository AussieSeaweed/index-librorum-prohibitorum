#include <iostream>
#include <vector>
#define inf 999999999
using namespace std;

int endpoints[20002][2];
int N, dp[20002][2];

int solve(int n, int i) {
    if (dp[n][i] != -1) return dp[n][i];
    if (n == N + 1) return dp[n][i] = 0;
    int current_dif = endpoints[n][1] - endpoints[n][0];
    dp[n][i] = 1 + current_dif + min(abs(endpoints[n][!i] - endpoints[n + 1][0]) + solve(n + 1, 0),
            abs(endpoints[n][!i] - endpoints[n + 1][1]) + solve(n + 1, 1));
    return dp[n][i];
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        endpoints[i][0] = u;
        endpoints[i][1] = v;
    }

    endpoints[N + 1][0] = N;
    endpoints[N + 1][1] = N;
    endpoints[0][0] = 1;
    endpoints[0][1] = 1;

    for (int i = 0; i <= N + 1; i++) {
        dp[i][0] = -1;
        dp[i][1] = -1;
    }

    printf("%d", solve(0, 0) - 2);

    return 0;
}