#include <bits/stdc++.h>

class Edge {
public:
    int u, v, dist, speed;
    double time;

    Edge(int u, int v, int dist, int speed) {
        this->u = u;
        this->v = v;
        this->dist = dist;
        this->speed = speed;
        this->time = (double) dist / ((double) speed / 60.0);
    }

    Edge() {};
};

int N, M;

std::vector<Edge> dijkstra(std::vector<std::vector<Edge>>& graph) {
    std::vector<Edge> edgeTo(N + 1);
    std::vector<double> min(N + 1, INFINITY);
    std::vector<bool> visited(N + 1, false);

    min[1] = 0;

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
            if (min[e.v] > min[minNode] + e.time) {
                edgeTo[e.v] = e;
                min[e.v] = min[minNode] + e.time;
            }
        }
    }

    return edgeTo;
}

int main() {
    scanf("%d%d", &N, &M);

    std::vector<std::vector<Edge>> graph(N + 1);

    while (M--) {
        int m, n, d, s;
        scanf("%d%d%d%d", &m, &n, &d, &s);
        graph[m].emplace_back(m, n, d, s);
        graph[n].emplace_back(n, m, d, s);
    }

    double delayed = 0;
    int count = 0;

    std::vector<Edge> edgeTo = dijkstra(graph);

    for (int i = N; i != 1; i = edgeTo[i].u) {
        delayed += edgeTo[i].dist / (edgeTo[i].speed * 0.75 / 60.0) - edgeTo[i].time;
        count++;
    }

    printf("%d\n%d", count, (int) round(delayed));

    return 0;
}