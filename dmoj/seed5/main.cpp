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
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

struct Flow_Edge {
    int from, to;
    long long capacity, flow;
    Flow_Edge(int from, int to, long long capacity) : from{ from }, to{ to }, capacity{ capacity }, flow{ 0 } {}
    int other(int node) { return node == from ? to : from; }
    long long get_residual_capacity_to(int node) { return node == to ? capacity - flow : flow; }
    void add_residual_capacity_to(int node, long long delta) { node == to ? flow += delta : flow -= delta; }
};

int N, M;
long long dist[200];
vector<Flow_Edge *> graph[200];

bool bfs(int source, int sink, int num_nodes, long long level[], vector<Flow_Edge *> graph[]) {
    fill(level, level + num_nodes, INF);
    queue<int> q;
    q.push(source);
    level[source] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (Flow_Edge *adj_edge : graph[node]) {
            int other = adj_edge->other(node);
            if (adj_edge->get_residual_capacity_to(other) && level[other] == INF) {
                level[other] = level[node] + 1;
                q.push(other);
            }
        }
    }

    return level[sink] != INF;
}

long long dfs(int node, int sink, long long pushed_flow, const long long level[], vector<Flow_Edge *> graph[]) {
    if (node == sink) return pushed_flow;
    long long leftover_flow = pushed_flow;
    for (Flow_Edge *adj_edge : graph[node]) {
        int other = adj_edge->other(node);
        if (level[node] + 1 == level[other] && adj_edge->get_residual_capacity_to(other) && leftover_flow) {
            long long sent_flow = dfs(other, sink, min(adj_edge->get_residual_capacity_to(other), leftover_flow), level, graph);
            adj_edge->add_residual_capacity_to(other, sent_flow);
            leftover_flow -= sent_flow;
        }
    }
    return pushed_flow - leftover_flow;
}

long long dinic(int source, int sink, int num_nodes, long long level[], vector<Flow_Edge *> graph[]) {
    long long total_flow = 0;

    while (bfs(source, sink, num_nodes, level, graph)) {
        total_flow += dfs(source, sink, INF, level, graph);
    }

    return total_flow;
}

int main() {
    scan(N);
    for (int i = 1; i < N; i++) {
        int e;
        scan(e);
        Flow_Edge *edge = new Flow_Edge(i, i + N, e);
        graph[i].push_back(edge);
        graph[i + N].push_back(edge);
    }
    scan(M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scan(u);
        scan(v);
        Flow_Edge *edge = new Flow_Edge(u + N, v, inf);
        graph[u + N].push_back(edge);
        graph[v].push_back(edge);
    }
    printf("%lld\n", dinic(1, N, 2 * N, dist, graph));
    return 0;
}