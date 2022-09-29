#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> graph[10001];
bool visited[10001];
int N, C, K, weight[10001], cherries[10001];

int dfs(int node) {
    visited[node] = true;
    int ans = 0;

    for (pair<int, int> p : graph[node]) {
        int adj = p.first;
        int w = p.second;
        if (!visited[adj]) {
            ans += dfs(adj);
            weight[node] += weight[adj] + w;
            cherries[node] += cherries[adj];
            if (cherries[adj] >= C && weight[adj] + w <= K) ans++;
        }
    }

    return ans;
}

int main() {
    scanf("%d%d%d", &N, &C, &K);
    for (int i = 1; i <= N; i++) scanf("%d", cherries + i);
    for (int i = 1; i < N; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    printf("%d", dfs(1));
    return 0;
}