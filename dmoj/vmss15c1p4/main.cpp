#include <iostream>
#include <vector>

#define INFINITY 9999999

struct Edge {
    int v, w, d;

    Edge(int v, int w, int d) :v{v},w{w},d{d} {}
};

int T, N, M, G;
std::vector<bool> isBasic(2001, false);
std::vector<bool> visited(2001, false);
std::vector<int> min(2001, INFINITY);
std::vector<std::vector<Edge>> graph(2001);

void dijkstra(int source) {
    min[source] = 0;

    while (true) {
        int minNode = -1;

        for (int n = 0; n <= N; n++)
            if (!visited[n])
                if (minNode == -1 || min[n] < min[minNode])
                    minNode = n;

        if (minNode == -1) break;

        visited[minNode] = true;

        for (Edge adj_edge : graph[minNode]) {
            int dist = min[minNode] + adj_edge.d;
            if (dist < min[adj_edge.w])
                min[adj_edge.w] = dist;
        }
    }
}

int main() {
    scanf("%d%d%d%d", &T, &N, &M, &G);

    while (G--) {
        int b;
        scanf("%d", &b);
        isBasic[b] = true;
    }

    while (M--) {
        int v, w, d;
        scanf("%d%d%d", &v, &w, &d);
        graph[v].emplace_back(v, w, d);
    }

    dijkstra(0);

    int count = 0;

    for (int i = 1; i <= N; i++)
        if (isBasic[i] && min[i] <= T)
            count++;

    printf("%d", count);

    return 0;
}