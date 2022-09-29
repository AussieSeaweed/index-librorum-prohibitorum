#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

std::vector<std::set<int>> graph(100);
std::vector<std::set<int, std::greater<int>>> igraph(100);
std::vector<bool> visited(100, false);

void topological_sort(int node, std::vector<int>& topo) {
    visited[node] = true;

    for (int adj : igraph[node]) {
        if (!visited[adj]) {
            topological_sort(adj, topo);
        }
    }

    topo.push_back(node);
}

void setID(int node, int id, std::vector<int>& ids) {
    ids[node] = id;

    for (int adj : graph[node]) {
        if (ids[adj] == -1) {
            setID(adj, id, ids);
        }
    }
}

bool kosaraju(std::vector<std::set<int>>& graph, std::vector<int>& topo, int N) {
    std::vector<int> ids(N + 1, -1);
    int id = 0;

    for (int i : std::vector<int> {topo.rbegin(), topo.rend()}) {
        if (ids[i] == -1) {
            setID(i, id++, ids);
        }
    }

    for (int i = 0; i < id; i++)
        if (std::count(ids.begin(), ids.end(), i) != 1)
            return false;

    return true;
}

int main() {
    graph[7].insert(1);
    graph[4].insert(1);
    graph[1].insert(2);
    graph[4].insert(3);
    graph[5].insert(3);

    igraph[1].insert(7);
    igraph[1].insert(4);
    igraph[2].insert(1);
    igraph[3].insert(4);
    igraph[3].insert(5);

    int maxNode = 7;

    while (true) {
        int v, w;
        scanf("%d%d", &v, &w);

        if (!v && !w) break;

        graph[w].insert(v);
        igraph[v].insert(w);

        maxNode = std::max(maxNode, std::max(v, w));
    }

    std::vector<int> topo;

    for (int i = maxNode; i >= 1; i--) {
        if (!visited[i])
            topological_sort(i, topo);
    }

    if (kosaraju(graph, topo, maxNode)) {
        for (int i  : std::vector<int> {topo.rbegin(), topo.rend()})
            printf("%d ", i);
    } else {
        printf("Cannot complete these tasks. Going to bed.");
    }
}