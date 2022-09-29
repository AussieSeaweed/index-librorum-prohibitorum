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
    int u, v, i;
    long long w;
    Edge(int u, int v, int i, long long w) : u{ u }, v{ v }, i{ i }, w{ w } {}
    int other(int node) { return node == v ? u : v; }
};

struct Event {
    int node;
    long long weight;
    Event(int node, long long weight) : node{ node }, weight{ weight } {}
    bool operator>(const Event &that) const {
        return weight > that.weight;
    }
};

bool visited[100001];
int N, M, A, B;
long long C, dist[100001];
vector<Edge *> graph[100001];

bool dijkstra(int i) {
    fill(dist, dist + N + 1, INF);
    fill(visited, visited + N + 1, false);
    priority_queue<Event, vector<Event>, greater<Event>> pq;
    dist[A] = 0;
    pq.emplace(A, 0);

    while (!pq.empty()) {
        Event e = pq.top();
        pq.pop();
        int node = e.node;

        if (visited[node]) continue;
        visited[node] = true;

        for (Edge *adj_edge : graph[node]) {
            if (adj_edge->i <= i) {
                int other = adj_edge->other(node);
                if (dist[other] > dist[node] + adj_edge->w) {
                    dist[other] = dist[node] + adj_edge->w;
                    pq.emplace(other, dist[other]);
                }
            }
        }
    }

    return dist[B] < C;
}

int main() {
    scan(N);
    scan(M);

    for (int i = 0; i < M; i++) {
        int a, b;
        long long c;
        scan(a);
        scan(b);
        scan(c);
        Edge *edge = new Edge(a, b, i, c);
        graph[a].push_back(edge);
        graph[b].push_back(edge);
    }

    scan(A);
    scan(B);
    scan(C);

    int lo = 0, hi = M - 1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        if (dijkstra(mid)) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d", lo == M ? -1 : lo + 1);

    return 0;
}