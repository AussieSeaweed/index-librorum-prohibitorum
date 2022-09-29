#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_priority_queue = std::priority_queue<T>;
inline int ffs(int x) { return __builtin_ffs(x) - 1; }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x) - 1; }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

struct Edge {
    int u, v;
    long long w;
    Edge(int u, int v, long long w) : u{ u }, v{ v }, w{ w } {}
    int other(int node) { return node == u ? v : u; }
};

int N, M;
long long dist[1001];
vector<Edge *> graph[1001];
Edge *edge_to[1001];

void dijkstra(int source, int num_nodes, long long dist[], Edge *edge_to[], vector<Edge *> graph[]) {
    min_priority_queue<pair<long long, int>> pq;
    fill(dist, dist + num_nodes, INF);
    fill(edge_to, edge_to + num_nodes, nullptr);
    dist[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty()) {
        pair<long long, int> event = pq.top();
        pq.pop();
        int node = event.second;

        if (dist[node] != event.first) continue;

        for (Edge *adj_edge : graph[node]) {
            int other = adj_edge->other(node);
            if (dist[other] > dist[node] + adj_edge->w) {
                dist[other] = dist[node] + adj_edge->w;
                edge_to[other] = adj_edge;
                pq.emplace(dist[other], other);
            }
        }
    }
}

int main() {
    scan(N);
    scan(M);
    while (M--) {
        int u, v, w;
        scan(u);
        scan(v);
        scan(w);
        Edge *edge = new Edge(u, v, w);
        graph[u].push_back(edge);
        graph[v].push_back(edge);
    }
    dijkstra(1, N + 1, dist, edge_to, graph);
    for (int i = 1; i <= N; i++)
        printf("%lld\n", dist[i] == INF ? -1 : dist[i]);
    return 0;
}