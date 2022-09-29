#include <iostream>
#include <vector>
#define inf 999999999
using namespace std;

vector<vector<int>> dp(1000, vector<int>(1001, -1));
vector<int> cost(1000);
int N;

int solve(int n, int pred) {
    if (n < 0 || n >= N) return inf;
    if (dp[n][pred] != -1) return dp[n][pred];
    if (n == N - 1) return dp[n][pred] = cost[n];
    if (pred == 0) return dp[n][pred] = solve(n + 1, 1);
    return dp[n][pred] = cost[n] + min(solve(n - pred, pred), solve(n + pred + 1, pred + 1));
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", &cost[i]);
    printf("%d", solve(0, 0));
    return 0;
}