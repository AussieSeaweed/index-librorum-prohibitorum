#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#define INFINITY 999999999
using namespace std;

struct Edge {
    int from, to, weight;
    Edge(int from, int to, int weight) :from{from}, to{to}, weight{weight} {}
};

struct Event {
    int node, weight;
    Event(int node, int weight) :node{node}, weight{weight} {}
    bool operator>(Event that) const {
        return weight > that.weight;
    }
};

vector<int> dijkstra(int source, vector<vector<Edge>>& graph) {
    vector<int> dist(graph.size(), INFINITY);
    vector<int> visited(graph.size(), false);
    priority_queue<Event, vector<Event>, greater<Event>> pq;
    pq.emplace(source, 0);
    dist[source] = 0;

    while (!pq.empty()) {
        Event e = pq.top();
        pq.pop();

        int node = e.node;

        if (visited[node]) continue;
        visited[node] = true;

        for (Edge adjEdge : graph[node]) {
            int ndist = dist[node] + adjEdge.weight;
            if (ndist < dist[adjEdge.to]) {
                dist[adjEdge.to] = ndist;
                pq.emplace(adjEdge.to, ndist);
            }
        }
    }

    return dist;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        unordered_map<string, int> stoi;
        vector<vector<Edge>> graph(N + 1);
        for (int i = 1; i <= N; i++) {
            string name;
            cin >> name;
            stoi[name] = i;
            int p;
            scanf("%d", &p);
            while (p--) {
                int node, weight;
                scanf("%d%d", &node, &weight);
                graph[i].emplace_back(i, node, weight);
            }
        }
        int np;
        scanf("%d", &np);
        while (np--) {
            string from, to;
            cin >> from >> to;
            int f = stoi[from], t = stoi[to];
            vector<int> dist = dijkstra(f, graph);

            printf("%d\n", dist[t]);
        }
    }
    return 0;
}