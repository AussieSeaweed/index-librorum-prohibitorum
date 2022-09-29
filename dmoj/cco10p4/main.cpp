#include <iostream>
#include <vector>
#define INFINITY 999999999
using namespace std;

vector<vector<int>> cost(6);
vector<vector<int>> value(6);
vector<int> num(6);
vector<vector<int>> dp(6, vector<int>(3001, -1));
int T, N, B;

int solve(int t, int b) {
    if (t == 0 && b >= 0) return 0;
    if (b < 0) return -INFINITY;
    if (dp[t][b] != -1) return dp[t][b];

    dp[t][b] = -INFINITY;

    for (int i = 0; i < num[t]; i++) {
        dp[t][b] = max(dp[t][b], value[t][i] + solve(t - 1, b - cost[t][i]));
    }

    return dp[t][b];
}

int main() {
    scanf("%d%d", &T, &N);
    for (int i = 0; i < N; i++) {
        int c, v, t;
        scanf("%d%d%d", &c, &v, &t);
        cost[t].push_back(c);
        value[t].push_back(v);
        num[t]++;
    }
    scanf("%d", &B);
    printf("%d", solve(T, B) < 0 ? -1 : solve(T, B));
    return 0;
}