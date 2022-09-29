#include <bits/stdc++.h>
#define INF 999999999

class Edge {
public:
    int v, w, capacity, flow;

    Edge(int v, int w, int capacity) {
        this->v = v;
        this->w = w;
        this->capacity = capacity;
        this->flow = 0;
    }

    int other(int vertex) {
        if (vertex == v) return w;
        else return v;
    }

    int capacityTo(int vertex) {
        if (vertex == w) return capacity - flow;
        else return flow;
    }

    void addTo(int vertex, int delta) {
        if (vertex == w) flow += delta;
        else flow -= delta;
    }
};

std::vector<std::vector<Edge*>> graph(302);
std::vector<Edge*> edgeTo(302);

bool hasAugmentingPath(int s, int t) {
    std::vector<bool> visited(302, false);
    std::queue<int> q;

    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (Edge *e : graph[node]) {
            int other = e->other(node);
            if (!visited[other] && e->capacityTo(other)) {
                q.push(other);
                visited[other] = true;
                edgeTo[other] = e;
            }
        }
    }

    return visited[t];
}

int main() {
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);

    for (int i = 1; i <= n; i++) {
        auto *e = new Edge(0, i, 1);

        graph[0].push_back(e);
        graph[i].push_back(e);

        int k;
        scanf("%d", &k);

        while (k--) {
            int j;
            scanf("%d", &j);

            j += 100;

            auto *e_ = new Edge(i, j, 1);

            graph[i].push_back(e_);
            graph[j].push_back(e_);
        }
    }

    std::vector<bool> categorized(101);

    for (int i = 1; i <= p; i++) {
        int l;
        scanf("%d" ,&l);

        while (l--) {
            int t;
            scanf("%d", &t);

            categorized[t] = true;

            auto *e = new Edge(t + 100, i + 200, 1);

            graph[t + 100].push_back(e);
            graph[i + 200].push_back(e);
        }

        int r;
        scanf("%d", &r);

        auto *e = new Edge(i + 200, 301, r);

        graph[i + 200].push_back(e);
        graph[301].push_back(e);
    }

    for (int i = 1; i <= 100; i++) {
        if (!categorized[i]) {
            auto *e = new Edge(i + 100, 301, 1);

            graph[i + 100].push_back(e);
            graph[301].push_back(e);
        }
    }

    int value = 0;

    while (hasAugmentingPath(0, 301)) {
        int min_flow = INFINITY;

        for (int v = 301; v != 0; v = edgeTo[v]->other(v))
            min_flow = std::min(min_flow, edgeTo[v]->capacityTo(v));

        for (int v = 301; v != 0; v = edgeTo[v]->other(v))
            edgeTo[v]->addTo(v, min_flow);

        value += min_flow;
    }

    printf("%d", value);

    return 0;
}