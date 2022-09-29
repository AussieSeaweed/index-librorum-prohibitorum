#include <bits/stdc++.h>

int N, M;
std::vector<int> visited(10001, false);
std::vector<int> ids(10001, -1);
std::vector<std::set<int>> graph(10001);
std::vector<std::set<int>> igraph(10001);
std::vector<int> topo;

void topoSort(int i) {
    visited[i] = true;
    for (int adj : graph[i]) {
        if (!visited[adj]) {
            topoSort(adj);
        }
    }
    topo.push_back(i);
}

void dfs(int i, int id) {
    ids[i] = id;
    for (int adj : igraph[i]) {
        if (ids[adj] == -1) {
            dfs(adj, id);
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);

    while (M--) {
        int a, b;
        scanf("%d%d", &a, &b);
        graph[a].insert(b);
        igraph[b].insert(a);
    }

    for (int i = 1; i <= N; i++) {
        if (!visited[i])
            topoSort(i);
    }

    int count = 1;
    for (int i = N-1; i >= 0; i--) {
        if (ids[topo[i]] == -1) {
            dfs(topo[i], count++);
        }
    }

    std::set<int> visited;
    bool flag = false;
    for (int i = 1; i <= N && !flag; i++) {
        if (visited.count(ids[i])) {
            printf("N");
            flag = true;
        }
        visited.insert(ids[i]);
    }
    if (!flag) {
        printf("Y");
    }
}