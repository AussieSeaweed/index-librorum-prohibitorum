#include <iostream>
#include <vector>
#define INFINITY 99999999

std::vector<std::vector<int>> graph(10001);
std::vector<int> dist(10001, INFINITY);
int N;

void dfs(int node, int d) {
    dist[node] = d;

    for (int adj :graph[node])
        if (dist[adj] == INFINITY)
            dfs(adj, d + 1);
}

int height() {
    dfs(1, 0);

    int maxNode = -1;
    int max = -1;

    for (int i = 1; i <= N; i++)
        if (dist[i] > max) {
            max = dist[i];
            maxNode = i;
        }

    std::fill(dist.begin(), dist.end(), INFINITY);
    dfs(maxNode, 0);

    max = -1;

    for (int i = 1; i <= N; i++)
        if (dist[i] > max)
            max = dist[i];

    return max;
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N - 1; i++) {
        int v, w;
        scanf("%d%d", &v, &w);
        graph[v].push_back(w);
        graph[w].push_back(v);
    }

    printf("%d", height());

    return 0;
}