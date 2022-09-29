#include <iostream>
#include <vector>
#define INF 999999999

class Edge {
public:
    int v, w, dist;

    Edge(int v, int w, int dist) {
        this->v = v;
        this->w = w;
        this->dist = dist;
    }
};

int N, M, B, Q;

std::vector<int> dijkstra(std::vector<std::vector<Edge>> graph, int source) {
    std::vector<int> min(N + 1, INF);
    std::vector<bool> visited(N + 1, false);

    min[source] = 0;

    while (true) {
        int minNode = -1;

        for (int i = 1; i <= N; i++) {
            if (!visited[i]) {
                if (minNode == -1 || min[minNode] > min[i])
                    minNode = i;
            }
        }

        if (minNode == -1) break;
        visited[minNode] = true;

        for (Edge e : graph[minNode]) {
            int other = e.w;
            int dist = min[minNode] + e.dist;
            if (min[other] > dist) {
                min[other] = dist;
            }
        }
    }

    return min;
}

int main() {
    scanf("%d%d%d%d", &N, &M, &B, &Q);

    std::vector<std::vector<Edge>> graph(N + 1);

    while (M--) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        graph[x].emplace_back(x, y, z);
        graph[y].emplace_back(y, x, z);
    }

    auto min = dijkstra(graph, B);

    while (Q--) {
        int i;
        scanf("%d", &i);
        printf("%d\n", min[i] == INF ? -1 : min[i]);
    }

    return 0;
}