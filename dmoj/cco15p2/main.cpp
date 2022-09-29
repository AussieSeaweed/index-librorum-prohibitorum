#include <iostream>
#include <vector>
#define INFINITY 99999999
using namespace std;

struct Edge {
    int from, to, weight;
    Edge(int from, int to, int weight) :from{from}, to{to}, weight{weight} {}
};

int N, M;
vector<vector<Edge>> graph(18);
vector<vector<int>> dp(18, vector<int>(1 << 18, -1));

int solve(int node, int bitmask) {
    if (node == N - 1) return 0;
    if (dp[node][bitmask] != -1) return dp[node][bitmask];
    int maxVal = -INFINITY;
    for (Edge adjEdge : graph[node])
        if (bitmask & (1 << adjEdge.to))
            maxVal = max(maxVal, solve(adjEdge.to, bitmask ^ (1 << adjEdge.to)) + adjEdge.weight);

    return dp[node][bitmask] = maxVal;
}

int main() {
    scanf("%d%d", &N, &M);
    while (M--) {
        int v, w, d;
        scanf("%d%d%d", &v, &w, &d);
        graph[v].emplace_back(v, w, d);
    }
    printf("%d", solve(0, ((1 << N) - 1) ^ 1));
    return 0;
}