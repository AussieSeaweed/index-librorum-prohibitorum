#include <iostream>
#include <vector>
#include <queue>
#define INFINITY 999999999
using namespace std;

struct Edge {
    int from, to, weight;
    Edge(int from, int to, int weight) :from{from},to{to}, weight{weight} {}
};

struct Event {
    int node, weight;
    Event(int node, int weight) :node{node}, weight{weight} {}
    bool operator>(Event that) const {
        return weight > that.weight;
    }
};

vector<vector<Edge>> graph(500001);
vector<vector<Edge>> igraph(500001);
vector<Edge> secret;
int N, M, D;

vector<int> dijkstra(int source, bool inverted) {
    void *g_ptr;
    if (inverted)
        g_ptr = &igraph;
    else
        g_ptr = &graph;
    vector<vector<Edge>>& g = * (vector<vector<Edge>> *) g_ptr;

    priority_queue<Event, vector<Event>, greater<Event>> pq;
    vector<int> dist(N + 1, INFINITY);
    vector<bool> visited(N + 1, false);
    pq.emplace(source, 0);
    dist[source] = 0;

    while (!pq.empty()) {
        Event e = pq.top();
        pq.pop();

        int node = e.node;

        if (visited[node]) continue;
        visited[node] = true;

        for (Edge adj_edge : g[node]) {
            int n_dist = dist[node] + adj_edge.weight;
            if (n_dist < dist[adj_edge.to]) {
                dist[adj_edge.to] = n_dist;
                pq.emplace(adj_edge.to, n_dist);
            }
        }
    }

    return dist;
}

int main() {
    scanf("%d%d", &N, &M);

    while (M--) {
        int a, b, k;
        scanf("%d%d%d", &a, &b, &k);
        graph[a].emplace_back(a, b, k);
        igraph[b].emplace_back(b, a, k);
    }

    scanf("%d", &D);

    while (D--) {
        int a, b, g;
        scanf("%d%d%d", &a, &b, &g);
        secret.emplace_back(a, b, g);
    }

    vector<int> dist1 = dijkstra(1, false);
    vector<int> dist2 = dijkstra(N, true);

    int ans = dist1[N];

    for (Edge passage : secret) {
        ans = min(dist1[passage.from] + passage.weight + dist2[passage.to], ans);
    }

    printf("%d", ans >= INFINITY ? -1 : ans);

    return 0;
}