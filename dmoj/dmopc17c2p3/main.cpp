#include <bits/stdc++.h>
#define INFINITY 99999999

int N, R;
int a, b;
std::vector<std::vector<int>> graph(200001);
std::vector<int> danger;
std::vector<int> min(200001, INFINITY);
std::queue<int> q;

void bfs() {
    std::vector<int> prev(200001, -1);
    std::queue<int> q;
    q.push(a);
    prev[a] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int adj : graph[node]) {
            if (prev[adj] == -1) {
                q.push(adj);
                prev[adj] = node;
            }
        }
    }

    for (int node = b; node != 0; node = prev[node]) {
        ::q.push(node);
        min[node] = 0;
    }
}

int main() {
    scanf("%d%d", &N, &R);

    for (int i = 1; i < N; i++) {
        int v, w;
        scanf("%d%d", &v, &w);
        graph[v].push_back(w);
        graph[w].push_back(v);
    }

    while (R--) {
        int n;
        scanf("%d", &n);
        danger.push_back(n);
    }

    scanf("%d%d", &a, &b);

    bfs();

    while (!q.empty()) {
        int node = q.front(); q.pop();

        for (int adj : graph[node]) {
            if (min[adj] == INFINITY) {
                min[adj] = min[node] + 1;
                q.push(adj);
            }
        }
    }

    int minDist = INFINITY;

    for (int bunny : danger) {
        minDist = std::min(minDist, min[bunny]);
    }

    printf("%d", minDist);

    return 0;
}