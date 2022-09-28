#include <iostream>
#include <vector>
#include <algorithm>

int N;

void dfs_topo(int node, std::vector<bool>& visited, std::vector<int>& topo, std::vector<std::vector<int>>& graph) {
    visited[node] = true;

    for (int adj : graph[node])
        if (!visited[adj])
            dfs_topo(adj, visited, topo, graph);

    topo.push_back(node);
}

void setID(int node, int id, std::vector<int>& ids, std::vector<std::vector<int>>& graph) {
    ids[node] = id;

    for (int adj : graph[node])
        if (ids[adj] == -1)
            setID(adj, id, ids, graph);
}

std::pair<std::vector<int>, int> korasaju(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& igraph) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> topo;
    std::vector<int> ids(graph.size(), -1);

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs_topo(i, visited, topo, igraph);
        }
    }

    int count = 0;

    while (!topo.empty()) {
        int i = topo.back(); topo.pop_back();

        if (ids[i] == -1) {
            setID(i, count++, ids, graph);
        }
    }

    return {ids, count};
}

int main() {
    int _;
    scanf("%d", &_);

    while (_--) {
        scanf("%d", &N);

        std::vector<std::vector<int>> graph(N + 1);
        std::vector<std::vector<int>> igraph(N + 1);

        for (int i = 1; i <= N; i++) {
            int M;
            scanf("%d", &M);

            while (M--) {
                int w;
                scanf("%d", &w);
                graph[w].push_back(i);
                igraph[i].push_back(w);
            }
        }

        auto ids_c = korasaju(graph, igraph);

        auto ids = ids_c.first;
        auto c = ids_c.second;

        std::vector<int> indegree(c, 0);

        for (int i = 1; i <= N; i++) {
            for (int adj : graph[i]) {
                if (ids[i] != ids[adj]) {
                    indegree[ids[adj]]++;
                }
            }
        }

        int count = 0;
        int winningID = -1;

        for (int id = 0; id < c; id++) {
            if (!indegree[id]) {
                count++;
                winningID = id;
            }
        }

        int ans = 0;

        for (int i = 1; i <= N; i++) {
            if (ids[i] == winningID) ans++;
        }

        if (count == 1) printf("%d\n", ans);
        else printf("0\n");
    }

    return 0;
}