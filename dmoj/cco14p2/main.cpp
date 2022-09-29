#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Edge {
    int x, y, l, c, t, tc;
    Edge(int x, int y, int l, int c) : x{ x }, y{ y }, l{ l }, c{ c } {}
    int other(int node) { return node == x ? y : x; }
};

struct Event {
    int node, weight;
    Event(int node, int weight) : node{ node }, weight{ weight } {}
    bool operator>(const Event &that) const {
        return weight > that.weight;
    }
};

int N, M, A, B, Q, dist1[100001], dist2[100001];
vector<Edge *> graph[100001], igraph[100001], edges;

void dijkstra(int src, int dist[], vector<Edge *> g[]) {
    fill(dist, dist + N + 1, inf);
    priority_queue<Event, vector<Event>, greater<Event>> pq;
    pq.emplace(src, 0);
    dist[src] = 0;

    while (!pq.empty()) {
        Event e = pq.top();
        pq.pop();
        int node = e.node;

        for (Edge *edge : g[node]) {
            int other = edge->other(node);
            if (dist[other] > dist[node] + edge->l) {
                dist[other] = dist[node] + edge->l;
                pq.emplace(other, dist[other]);
            }
        }
    }
}

int main() {
    scan(N);
    scan(M);
    scan(A);
    scan(B);

    while (M--) {
        int x, y, l, c;
        scan(x);
        scan(y);
        scan(l);
        scan(c);

        edges.push_back(new Edge(x, y, l, c));
        graph[x].push_back(edges.back());
        igraph[y].push_back(edges.back());
    }

    dijkstra(A, dist1, graph);
    dijkstra(B, dist2, igraph);

    for (Edge *e : edges) {
        if (dist1[e->x] != inf && dist2[e->y] != inf)
            e->t = dist1[e->x] + e->l + dist2[e->y];
        else
            e->t = inf;
    }

    sort(edges.begin(), edges.end(), [&] (Edge *a, Edge *b) -> bool {
        return a->t < b->t;
    });

    edges[0]->tc = edges[0]->c;

    for (int i = 1; i < edges.size(); i++) {
        edges[i]->tc = edges[i]->c + edges[i - 1]->tc;
    }

    scan(Q);

    while (Q--) {
        int d;
        scan(d);
        int lo = 0, hi = edges.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (edges[mid]->t <= d) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        --lo;
        if (lo >= 0) {
            printf("%d\n", edges[lo]->tc);
        } else {
            printf("0\n");
        }
    }

    return 0;
}