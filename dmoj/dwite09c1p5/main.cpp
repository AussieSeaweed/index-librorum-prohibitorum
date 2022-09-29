#include <iostream>
#include <vector>
#include <algorithm>

void topological_sort(int node, std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& topo) {
    visited[node] = true;

    for (int adj : graph[node]) {
        if (!visited[adj]) {
            topological_sort(adj, graph, visited, topo);
        }
    }

    topo.push_back(node);
}

void setID(int node, int id, std::vector<std::vector<int>>& graph, std::vector<int>& ids) {
    ids[node] = id;

    for (int adj : graph[node]) {
        if (ids[adj] == -1) {
            setID(adj, id, graph, ids);
        }
    }
}

long kosaraju(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& igraph, int M) {
    std::vector<bool> visited(M + 1, false);
    std::vector<int> topo;

    for (int i = 1; i <= M; i++) {
        if (!visited[i]) {
            topological_sort(i, igraph, visited, topo);
        }
    }

    std::vector<int> ids(M + 1, -1);
    int id = 0;

    for (int i : std::vector<int>{topo.rbegin(), topo.rend()})
        if (ids[i] == -1)
            setID(i, id++, graph, ids);

    long ans = -1;

    for (int i = 0; i < id; i++)
        ans = std::max(ans, std::count(ids.begin(), ids.end(), i));

    return ans;
}

int main() {
    int _ = 5;
    while (_--) {
        int N;
        scanf("%d", &N);
        std::vector<std::vector<int>> graph(101);
        std::vector<std::vector<int>> igraph(101);
        int M = 0;

        while (N--) {
            int v, w;
            scanf("%d%d", &v, &w);
            graph[v].push_back(w);
            igraph[w].push_back(v);
            M = std::max(M, std::max(w, v));
        }

        printf("%ld\n", kosaraju(graph, igraph, M));
    }
    return 0;
}