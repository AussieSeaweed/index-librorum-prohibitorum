#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Edge {
    int u, v, l, start;
    bool used = false;
    Edge(int u, int v, int l) : u{ u }, v{ v }, l{ l } {}
    int other(int node) { return node == u ? v : u; }
} *mat[1001][1001];

struct Event {
    int node, w;
    Event(int node, int w) : node{ node }, w{ w } {}
    bool operator>(const Event &that) const {
        return w > that.w;
    }
};

int N, M, A, B, K, G, dist[1001], gpath[1000];
vector<Edge *> graph[1001];
priority_queue<Event, vector<Event>, greater<Event>> pq;

void dijkstra() {
    fill(dist, dist + N + 1, inf);
    dist[A] = K;
    pq.emplace(A, dist[A]);

    while (!pq.empty()) {
        Event e = pq.top(); pq.pop();
        int node = e.node;

        for (Edge *adj_edge : graph[node]) {
            int other = adj_edge->other(node);
            int ndist = adj_edge->used && adj_edge->start <= dist[node] && dist[node] < adj_edge->start + adj_edge->l ? adj_edge->start + 2 * adj_edge->l : dist[node] + adj_edge->l;
            if (dist[other] > ndist) {
                dist[other] = ndist;
                pq.emplace(other, dist[other]);
            }
        }
    }
}

int main() {
    pscan(N);
    pscan(M);
    pscan(A);
    pscan(B);
    pscan(K);
    pscan(G);

    for (int i = 0; i < G; i++) pscan(gpath[i]);

    while (M--) {
        int u, v, l;
        pscan(u);
        pscan(v);
        pscan(l);
        Edge *e = new Edge(u, v, l);
        mat[u][v] = e;
        mat[v][u] = e;
        graph[u].push_back(e);
        graph[v].push_back(e);
    }

    for (int i = 0, dist = 0; i < G - 1; dist += mat[gpath[i]][gpath[i + 1]]->l, i++) {
        mat[gpath[i]][gpath[i + 1]]->used = true;
        mat[gpath[i]][gpath[i + 1]]->start = dist;
    }

    dijkstra();

    printf("%d\n", dist[B] - K);
    return 0;
}