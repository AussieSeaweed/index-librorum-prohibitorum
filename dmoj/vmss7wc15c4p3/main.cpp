#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

const int MAX_NODE = 99999;
int dist1[MAX_NODE + 1];
int pred1[MAX_NODE + 1];
int dist2[MAX_NODE + 1];
int pred2[MAX_NODE + 1];
vector<pair<int, int>> graph[MAX_NODE + 1];

struct Event {
    int node, weight;

    Event(int node, int weight) : node{ node }, weight{ weight } {}

    bool operator>(const Event &that) const {
        return weight > that.weight;
    }
};

void dijkstra1(int source) {
    fill(begin(dist1), end(dist1), inf);
    priority_queue<Event, vector<Event>, greater<Event>> pq;
    pq.emplace(source, 0);
    pred1[source] = -1;
    dist1[source] = 0;

    while (!pq.empty()) {
        Event e = pq.top();
        pq.pop();
        int node = e.node;

        for (pair<int, int> adj_edge : graph[node]) {
            int adj = adj_edge.first;
            int weight = adj_edge.second;
            if (dist1[adj] > dist1[node] + weight) {
                dist1[adj] = dist1[node] + weight;
                pred1[adj] = node;
                pq.emplace(adj, dist1[adj]);
            }
        }
    }
}

void dijkstra2(int source) {
    fill(begin(dist2), end(dist2), inf);
    priority_queue<Event, vector<Event>, greater<Event>> pq;
    pq.emplace(source, 0);
    pred2[source] = -1;
    dist2[source] = 0;

    while (!pq.empty()) {
        Event e = pq.top();
        pq.pop();
        int node = e.node;

        for (pair<int, int> adj_edge : graph[node]) {
            int adj = adj_edge.first;
            int weight = adj_edge.second;
            if (dist2[adj] > dist2[node] + weight) {
                dist2[adj] = dist2[node] + weight;
                pred2[adj] = node;
                pq.emplace(adj, dist2[adj]);
            }
        }
    }
}

int N, M;

int main() {
    scan(N);
    scan(M);

    while (M--) {
        int u, v, w;
        scan(u);
        scan(v);
        scan(w);

        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    dijkstra1(0);
    dijkstra2(N - 1);

    int ans = 0;

    for (int i = 0; i < N; i++) {
        if (dist1[i] != inf && dist2[i] != inf)
            ans = max(ans, dist1[i] + dist2[i]);
    }

    printf("%d\n", ans);

    return 0;
}