#include <iostream>
#include <vector>
#define INFINITY 99999999
using namespace std;

vector<vector<int>> tm(100, vector<int>(100));
vector<vector<int>> xp(100, vector<int>(100));
vector<vector<vector<int>>> dp(100, vector<vector<int>>(100, vector<int>(100, -1)));
vector<int> L(100);
int N, T;

int solve(int t, int n, int l) {
    if (t == 0) return 0;
    if (t < 0) return -INFINITY;
    if (n < 0) return -INFINITY;
    if (l < 0) {
        if (--n < 0) return -INFINITY;
        l = L[n] - 1;
    }
    if (dp[t][n][l] != -1) return dp[t][n][l];

    return dp[t][n][l] = max(xp[n][l] + solve(t - tm[n][l], n - 1, n - 1 < 0 ? -1 : L[n - 1]), solve(t, n, l - 1));
}

int main() {
    scanf("%d%d", &N, &T);

    for (int i = 0; i < N; i++) {
        scanf("%d", &L[i]);
        scanf("%d%d", &tm[i][0], &xp[i][0]);
        for (int j = 1; j < L[i]; j++) {
            scanf("%d%d", &tm[i][j], &xp[i][j]);
            tm[i][j] += tm[i][j - 1];
            xp[i][j] += xp[i][j - 1];
        }
    }

    int ans = -INFINITY;
    for (int t = T; t >= 0; t--) {
        ans = max(ans, solve(t, N - 1, L[N - 1] - 1));
    }
    printf("%d", ans);
    return 0;
}