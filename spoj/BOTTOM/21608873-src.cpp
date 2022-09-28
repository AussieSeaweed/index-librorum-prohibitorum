#include <iostream>
#include <vector>
#include <stack>

int V, E;

void dfs(int node, std::vector<bool>& visited, const std::vector<std::vector<int>>& graph) {
    visited[node] = true;

    for (int adj : graph[node])
        if (!visited[adj]) dfs(adj, visited, graph);
}

void topological_sort(int node, std::vector<bool>& visited, std::stack<int>& topo, const std::vector<std::vector<int>>& graph) {
    visited[node] = true;

    for (int adj : graph[node])
        if (!visited[adj])
            topological_sort(adj, visited, topo, graph);

    topo.push(node);
}

void setID(int node, std::vector<int>& id, int count, const std::vector<std::vector<int>>& graph) {
    id[node] = count;

    for (int adj : graph[node])
        if (id[adj] == -1)
            setID(adj, id, count, graph);
}

std::pair<std::vector<int>, int> korasaju(const std::vector<std::vector<int>>& igraph, const std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(V + 1, false);
    std::stack<int> topo;

    for (int i = 1; i <= V; i++)
        if (!visited[i])
            topological_sort(i, visited, topo, igraph);

    std::vector<int> id(V + 1, -1);
    int count = 0;

    while (!topo.empty()) {
        int i = topo.top();
        topo.pop();

        if (id[i] == -1)
            setID(i, id, count++, graph);
    }

    return {id, count};
}

int main() {
    while (true) {
        scanf("%d", &V);
        if (!V) break;
        scanf("%d", &E);

        std::vector<std::vector<int>> graph(V + 1);
        std::vector<std::vector<int>> igraph(V + 1);

        while (E--) {
            int v, w;
            scanf("%d%d", &v, &w);

            graph[v].push_back(w);
            igraph[w].push_back(v);
        }

        auto id_c = korasaju(igraph, graph);
        std::vector<int> id = id_c.first;
        int count = id_c.second;
        std::vector<int> valid(count, true);

        for (int i = 1; i <= V; i++) {
            if (valid[id[i]]) {
                for (int adj : graph[i]) {
                    if (id[adj] != id[i]) {
                        valid[id[i]] = false;
                        break;
                    }
                }
            }
        }

        for (int i = 1; i <= V; i++)
            if (valid[id[i]])
                printf("%d ", i);
        printf("\n");
    }

    return 0;
}