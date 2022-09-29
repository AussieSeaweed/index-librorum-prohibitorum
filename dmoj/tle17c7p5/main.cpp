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

struct Weighted_Flow_Edge {
    int from, to;
    long long capacity, flow;
    long double weight, weights[2];
    Weighted_Flow_Edge(int from, int to, long long capacity, long double weight) : from{ from }, to{ to }, capacity{ capacity }, weight{ weight }, weights{ -weight, weight }, flow{ 0 } {}
    int other(int node) { return node == from ? to : from; }
    long long get_residual_capacity_to(int node) { return node == to ? capacity - flow : flow; }
    void add_residual_capacity_to(int node, long long delta) { node == to ? flow += delta : flow -= delta; }
    long double get_weight_to(int node) { return weights[node == to]; }
};

int N, offset, M, C;
long double dist[202];
bool visited[202];
pair<int, int> males[100], females[100];
Weighted_Flow_Edge *edge_to[202];
Weighted_Flow_Edge *edge_list[10200], *critical_edges[10000];
vector<Weighted_Flow_Edge *> graph[202];

bool dijkstra(int source, int sink, int num_nodes, long double dist[], Weighted_Flow_Edge *edge_to[], vector<Weighted_Flow_Edge *> graph[]) {
    fill(dist, dist + num_nodes, INF);
    fill(edge_to, edge_to + num_nodes, nullptr);
    fill(visited, visited + num_nodes, false);
    min_priority_queue<pair<long double, int>> pq;
    dist[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty()) {
        pair<long double, int> event = pq.top();
        pq.pop();
        int node = event.second;

        if (visited[node]) continue;
        visited[node] = true;

        for (Weighted_Flow_Edge *adj_edge : graph[node]) {
            int other = adj_edge->other(node);
            if (adj_edge->get_residual_capacity_to(other) && dist[other] > dist[node] + adj_edge->get_weight_to(other)) {
                dist[other] = dist[node] + adj_edge->get_weight_to(other);
                edge_to[other] = adj_edge;
                pq.emplace(dist[other], other);
            }
        }
    }

    return dist[sink] != INF;
}

void reduce(int num_edges, const long double dist[], Weighted_Flow_Edge *edge_list[]) {
    for (int i = 0; i < num_edges; i++) {
        edge_list[i]->weights[1] += dist[edge_list[i]->from] - dist[edge_list[i]->to];
        edge_list[i]->weights[0] = 0;
    }
}

pair<long long, long double> min_cost_max_flow(int source, int sink, int num_nodes, int num_edges, long double dist[], Weighted_Flow_Edge *edge_to[], Weighted_Flow_Edge *edge_list[], vector<Weighted_Flow_Edge *> graph[]) {
    long long total_flow = 0;
    long double total_weight = 0;
    dijkstra(source, sink, num_nodes, dist, edge_to, graph);
    reduce(num_edges, dist, edge_list);

    while (dijkstra(source, sink, num_nodes, dist, edge_to, graph)) {
        reduce(num_edges, dist, edge_list);
        long long min_flow = INF;

        for (int node = sink; node != source; node = edge_to[node]->other(node))
            min_flow = min(min_flow, edge_to[node]->get_residual_capacity_to(node));

        for (int node = sink; node != source; node = edge_to[node]->other(node))
            edge_to[node]->add_residual_capacity_to(node, min_flow);

        total_flow += min_flow;
    }

    for (int i = 0; i < num_edges; i++)
        if (edge_list[i]->flow)
            total_weight += edge_list[i]->weight;

    return { total_flow, total_weight };
}

long double get_distance(pair<int, int> &a, pair<int, int> &b) {
    long double dx = a.first - b.first, dy = a.second - b.second;
    return hypot(dx, dy);
}

int main() {
    scan(N);
    for (int i = 0; i < N; i++) {
        scan(males[i].first);
        scan(males[i].second);
    }
    for (int i = 0; i < N; i++) {
        scan(females[i].first);
        scan(females[i].second);
    }

    for (int i = 0; i < N; i++) {
        edge_list[M] = new Weighted_Flow_Edge(200, i, 1, 0);
        graph[200].push_back(edge_list[M]);
        graph[i].push_back(edge_list[M]);
        M++;
        edge_list[M] = new Weighted_Flow_Edge(i + N, 201, 1, 0);
        graph[i + N].push_back(edge_list[M]);
        graph[201].push_back(edge_list[M]);
        M++;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long double dist = get_distance(males[i], females[j]);
            critical_edges[C++] = edge_list[M] = new Weighted_Flow_Edge(i, j + N, 1, dist);
            graph[i].push_back(edge_list[M]);
            graph[j + N].push_back(edge_list[M]);
            M++;
        }
    }
    pair<long long, long double> q = min_cost_max_flow(200, 201, 202, M, dist, edge_to, edge_list, graph);
    assert(q.first == N);
    for (int i = 0; i < C; i++) {
        if (critical_edges[i]->flow) {
            printf("%d %d\n", critical_edges[i]->from + 1, critical_edges[i]->to - N + 1);
        }
    }
    return 0;
}