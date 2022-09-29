#include <bits/stdc++.h>
#define INF 99999999

class Edge {
public:
    int a, b, t, h;

    Edge(int a, int b, int t, int h) {
        this->a = a;
        this->b = b;
        this->t = t;
        this->h = h;
    }
};

class Tuple {
public:
    int node, hull, weight;

    Tuple(int n, int h, int w) {
        node = n;
        hull = h;
        weight = w;
    }

    Tuple() {};
};

struct minimum_weight {
    bool operator () (Tuple a, Tuple b) {
        return a.weight > b.weight;
    }
};

int K, N, M, A, B;

std::vector<std::vector<Edge>> graph(2001);

std::vector<std::vector<int>> dijkstra() {
    std::vector<std::vector<int>> min(N+1, std::vector<int>(K+1, INF));
    std::vector<std::vector<bool>> visited(N+1, std::vector<bool>(K+1, false));
    std::priority_queue<Tuple, std::vector<Tuple>, minimum_weight> q;
    q.emplace(A, K, 0);
    min[A][K] = 0;

    while (!q.empty()) {
        Tuple min_tuple = q.top(); q.pop();
        if (visited[min_tuple.node][min_tuple.hull]) continue;

        int node = min_tuple.node, hull = min_tuple.hull, weight = min_tuple.weight;

        visited[node][hull] = true;

        for (Edge adj_edge : graph[node]) {
            int current = weight + adj_edge.t;
            int remaining_hull = hull - adj_edge.h;
            if (remaining_hull > 0 && current < min[adj_edge.b][remaining_hull]) {
                min[adj_edge.b][remaining_hull] = current;
                q.emplace(adj_edge.b, remaining_hull, current);
            }
        }
    }

    return min;
}

int main() {
    scanf("%d%d%d", &K, &N, &M);

    for (int i = 0; i < M; i++) {
        int a, b, t, h;
        scanf("%d%d%d%d", &a, &b, &t, &h);
        graph[a].emplace_back(a, b, t, h);
        graph[b].emplace_back(b, a, t, h);
    }

    scanf("%d%d", &A, &B);

    std::vector<std::vector<int>> min = dijkstra();

    int ans = INF;
    for (int w : min[B]) {
        ans = std::min(ans, w);
    }

    printf("%d", ans == INF ? -1 : ans);
}