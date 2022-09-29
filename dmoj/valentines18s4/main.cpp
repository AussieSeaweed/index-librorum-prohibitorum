#include <iostream>
#include <vector>

using namespace std;

long long factorial[200001], dp[200001], N, mod = 1000000007;
vector<int> graph[200001];

void init_factorial() {
    factorial[0] = 1;
    for (long long i = 1; i <= N; i++)
        factorial[i] = i * factorial[i - 1] % mod;
}

long long solve(int node) {
    if (dp[node] != -1) return dp[node];
    dp[node] = factorial[graph[node].size() + 1];

    for (int adj : graph[node])
        dp[node] = solve(adj) * dp[node] % mod;

    return dp[node];
}

int main() {
    scanf("%llu", &N);
    fill(dp, dp + N + 1, -1);
    init_factorial();
    for (int i = 1; i < N; i++) {
        int parent;
        scanf("%d", &parent);
        graph[parent].push_back(i);
    }
    printf("%lld", solve(0));
    return 0;
}