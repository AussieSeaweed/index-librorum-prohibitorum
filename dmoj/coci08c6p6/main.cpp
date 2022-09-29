#include <bits/stdc++.h>
#include <bits/extc++.h>
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_priority_queue = std::priority_queue<T>;
inline int ffs(int x) { return __builtin_ffs(x); }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x); }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename T> inline T gcd(const T &x, const T &y) { return std::__gcd(x, y); }
template<typename T, typename ...Ts> inline T gcd(const T &x, const Ts &...xs) { return std::__gcd(x, gcd(xs...)); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
template<typename T> inline void scan(T &x) { char c; bool sign; while ((x = getchar()) < '-'); sign = x == '-'; if (sign) while ((x = getchar()) < '0'); for(x -= '0'; '0' <= (c = getchar()); x = (x << 3) + (x << 1) + c - '0'); x = sign ? -x : x; }
template<typename T, typename ...Ts> inline void scan(T &x, Ts &...xs) { scan(x), scan(xs...); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

struct Edge {
    int from, to, flow, capacity;
    Edge(int from, int to, int capacity) : from{ from }, to{ to }, flow{}, capacity{ capacity } {}
    int other(int node) { return node == from ? to : from; }
    void add_residual_capacity_to(int node, int delta) { if (node == to) flow += delta; else flow -= delta; }
    int get_residual_capacity_to(int node) { return node == from ? flow : capacity - flow; }
};

int N, M, levels[1102], source, sink, rem[100];
pair<Edge *, Edge *> edges[1000];
Edge *linked[100];
vector<Edge *> graph[1102];
vector<triple<int, int, int>> purchases;
vector<int> ones, twos;

bool bfs() {
    fill(levels, levels + N + M + 2, -1);
    queue<int> q;
    q.push(source), levels[source] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (Edge *adj_edge : graph[node]) {
            int adj = adj_edge->other(node);
            if (levels[adj] == -1 && adj_edge->get_residual_capacity_to(adj)) {
                levels[adj] = levels[node] + 1;
                q.push(adj);
            }
        }
    }

    return levels[sink] != -1;
}

int dfs(int node, int pushed_flow) {
    if (node == sink) return pushed_flow;
    int tmp = pushed_flow;

    for (Edge *adj_edge : graph[node]) {
        int adj = adj_edge->other(node);
        if (levels[node] + 1 == levels[adj] && adj_edge->get_residual_capacity_to(adj) && tmp) {
            int cur = dfs(adj, min(adj_edge->get_residual_capacity_to(adj), tmp));
            adj_edge->add_residual_capacity_to(adj, cur);
            tmp -= cur;
        }
    }

    return pushed_flow - tmp;
}

void dinic() {
    while (bfs()) {
        dfs(source, inf);
    }
}

int main() {
    scan(N, M), sink = N + M, source = N + M + 1;

    for (int i = 0; i < N; i++) {
        int n;
        scan(n);
        Edge *edge = linked[i] = new Edge(i, sink, n);
        graph[i].push_back(edge);
        graph[sink].push_back(edge);
    }

    for (int i = 0, j = N; i < M; i++, j++) {
        int u, v;
        scan(u, v);
        u--, v--;
        Edge *e1 = new Edge(j, u, inf), *e2 = new Edge(j, v, inf), *e3 = new Edge(source, j, 2);
        graph[j].push_back(e1), graph[j].push_back(e2), graph[j].push_back(e3);
        graph[u].push_back(e1), graph[v].push_back(e2);
        graph[source].push_back(e3);
        edges[i] = {e1, e2};
    }

    dinic();

    for (int i = 0; i < M; i++)
        purchases.emplace_back(edges[i].first->to, edges[i].second->to, edges[i].first->flow);

    for (int i = 0; i < N; i++) {
        rem[i] = linked[i]->get_residual_capacity_to(sink);

        if (rem[i] >= 2)
            twos.push_back(i);
        else if (rem[i] == 1)
            ones.push_back(i);
    }

    for (int node : twos) {
        while (rem[node] >= 2) {
            purchases.emplace_back(node, node == 0 ? 1 : 0, 2);
            rem[node] -= 2;
        }

        if (rem[node] == 1)
            ones.push_back(node);
    }

    for (int i = 0; i < ones.size(); i += 2) {
        purchases.emplace_back(ones[i], ones[i + 1], 1);
    }

    printf("%d\n", purchases.size());

    for (triple<int, int, int> &purchase : purchases) {
        printf("%d %d %d\n", purchase.first + 1, purchase.second + 1, purchase.third);
    }

    return 0;
}