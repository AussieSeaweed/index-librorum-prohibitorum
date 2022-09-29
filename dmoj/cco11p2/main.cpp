#include <bits/stdc++.h>
#define INF 999999999

class Edge {
public:
    int v, w, t;
    bool s;

    Edge(int v, int w, int t, bool s) {
        this->v = v;
        this->w = w;
        this->t = t;
        this->s = s;
    }


};

class Event {
public:
    int N, D, S;

    Event(int N, int D, int S) {
        this->N = N;
        this->D = D;
        this->S = S;
    }

    bool operator > (Event that) const {
        return D > that.D;
    }
};

int S, N, E;

std::vector<std::vector<int>> dijkstra(std::vector<std::vector<Edge>>& graph) {
    std::vector<std::vector<int>> min(N, std::vector<int>(S + 1, INF));
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(S + 1, false));
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;

    min[0][S] = 0;
    pq.emplace(0, 0, S);

    while (!pq.empty()) {
        Event min_event = pq.top();
        pq.pop();

        int min_node = min_event.N;
        int min_dist = min_event.D;
        int min_sun = min_event.S;

        if (visited[min_node][min_sun]) continue;

        visited[min_node][min_sun] = true;

        for (Edge adj_edge : graph[min_node]) {
            int adj_node = adj_edge.w;
            int weight = min_dist + adj_edge.t;
            int left_sun = min_sun - (adj_edge.s ? adj_edge.t : 0);
            if (left_sun >= 0 && weight < min[adj_node][min_sun]) {
                min[adj_node][min_sun] = weight;
                pq.emplace(adj_node, weight, left_sun);
            }
        }
    }

    return min;
}

int main() {
    scanf("%d%d%d", &S, &N, &E);

    std::vector<std::vector<Edge>> graph(N);

    for (int i = 0; i < E; i++) {
        int v, w, t, s;
        scanf("%d%d%d%d", &v, &w, &t, &s);

        graph[v].emplace_back(v, w, t, s);
        graph[w].emplace_back(w, v, t, s);
    }

    std::vector<std::vector<int>> min = dijkstra(graph);

    int min_weight = INF;
    for (int i = 0; i <= S; i++) {
        if (min[N-1][i] < min_weight)
            min_weight = min[N - 1][i];
    }

    printf("%d", min_weight == INF ? -1 : min_weight);

    return 0;
}