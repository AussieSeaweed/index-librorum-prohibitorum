#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> graph(21);
std::vector<std::vector<bool>> isBridge(21, std::vector<bool>(21, false));
std::vector<int> parent(21, -1);
std::vector<int> depth(21);
std::vector<int> low(21);
std::vector<bool> visited(21, false);
std::vector<int> bc(21, -1);
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
                isBridge[node][adj] = isBridge[adj][node] = true;
        } else if (parent[node] != adj) {
            low[node] = std::min(low[node], depth[adj]);
        }
    }
}

void biconnectedComponents(int node, int id) {
    visited[node] = true;
    bc[node] = id;

    for (int adj : graph[node]) {
        if (!visited[adj] && !isBridge[node][adj]) {
            biconnectedComponents(adj, id);
        }
    }
}

bool atLeastSix(int lim) {
    for (int i = 0; i < lim; i++) {
        if (std::count(bc.begin(), bc.end(), i) >= 6) return true;
    }

    return false;
}

int main() {
    scanf("%d%d", &N, &M);

    while (M--) {
        int v, w;
        scanf("%d%d", &v, &w);
        graph[v].push_back(w);
        graph[w].push_back(v);
    }

    dfs(1, 0);

    std::fill(visited.begin(), visited.end(), false);
    int id = 0;

    for (int i = 1; i <= N; i++) {
        if (bc[i] == -1) {
            biconnectedComponents(i, id++);
        }
    }

    if (atLeastSix(id)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}