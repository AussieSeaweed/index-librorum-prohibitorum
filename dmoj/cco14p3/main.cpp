#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

long long dp[201][201][2], MOD = 1000000007;
vector<int> dgraph[201], agraph[201];
int N, W, M, in[201], out[201];

long long solve() {
    for (int i = N; i >= 0; i--) {
        dp[i][0][0] = 1;
        dp[i][1][1] = 1;

        for (int adj : dgraph[i]) {
            for (int j = W; j >= 0; j--) {
                long long is_not_w = 0, is_w = 0;
                for (int k = 0; k <= j; k++) {
                    is_not_w = (is_not_w + dp[i][j - k][0] * (dp[adj][k][0] + dp[adj][k][1])) % MOD;
                    is_w = (is_w + dp[i][j - k][1] * dp[adj][k][1]) % MOD;
                }
                dp[i][j][0] = is_not_w;
                dp[i][j][1] = is_w;
            }
        }

        for (int adj : agraph[i]) {
            for (int j = W; j >= 0; j--) {
                long long is_not_w = 0, is_w = 0;
                for (int k = 0; k <= j; k++) {
                    is_not_w = (is_not_w + dp[i][j - k][0] * (dp[adj][k][0] + dp[adj][k][1])) % MOD;
                    is_w = (is_w + dp[i][j - k][1] * dp[adj][k][0]) % MOD;
                }
                dp[i][j][0] = is_not_w;
                dp[i][j][1] = is_w;
            }
        }
    }

    return dp[0][W][0];
}

int main() {
    scanf("%d%d%d", &N, &W, &M);

    while (M--) {
        char t; int u, v;
        scanf(" %c%d%d", &t, &u, &v);
        in[v]++;
        out[u]++;
        if (t == 'A') {
            agraph[u].push_back(v);
        } else {
            dgraph[u].push_back(v);
        }
    }

    for (int i = 1; i <= N; i++)
        if (!in[i])
            agraph[0].push_back(i);

    printf("%lld", solve());
    return 0;
}