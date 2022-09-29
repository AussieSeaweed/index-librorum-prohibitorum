#include <bits/stdc++.h>

bool bfs(std::vector<std::set<int>>& g, int s, int d) {
    std::queue<int> q;
    std::vector<bool> visited(g.size(), false);
    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int n = q.front(); q.pop();

        if (n == d) return true;

        for (int adj : g[n]) {
            if (!visited[adj]) {
                q.push(adj);
                visited[adj] = true;
            }
        }
    }

    return false;
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);

    std::vector<std::set<int>> graph(N+1, std::set<int>());
    std::vector<std::pair<int,int>> ui;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        ui.push_back(std::make_pair(u,v));
        graph[u].insert(v);
    }

    for (int i = 0; i < M; i++) {
        graph[ui[i].first].erase(ui[i].second);

        if (bfs(graph, 1, N))
            printf("YES\n");
        else
            printf("NO\n");

        graph[ui[i].first].insert(ui[i].second);
    }

    return 0;
}