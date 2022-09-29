#include <iostream>
#include <vector>

std::vector<bool> visited(101, false);
std::vector<int> parent(101, -1);
std::vector<int> depth(101);
std::vector<int> low(101);
std::vector<std::vector<int>> graph(101);
std::vector<std::pair<int, int>> bridges;
int N, M;

void dfs(int node, int d) {
    visited[node] = true;
    depth[node] = low[node] = d;

    for (int adj : graph[node]) {
        if (!visited[adj]) {
            parent[adj] = node;
            dfs(adj, d + 1);

            low[node] = std::min(low[node], low[adj]);

            if (low[adj] > depth[node])
                bridges.emplace_back(node, adj);

        } else if (adj != parent[node]) {
            low[node] = std::min(low[node], depth[adj]);
        }
    }
}

int main() {
    int _ = 5;

    while (_--) {
        scanf("%d%d", &N, &M);

        std::fill(visited.begin(), visited.end(), false);
        graph.clear();
        graph.resize(N + 1);
        bridges.clear();

        while (M--) {
            int v, w;
            scanf("%d%d", &v, &w);

            graph[v].push_back(w);
            graph[w].push_back(v);
        }

        parent[1] = -1;
        dfs(1, 0);

        printf("%lu\n", bridges.size());
    }

    return 0;
}