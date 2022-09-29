#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scanu(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
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
template<typename _EuclideanRingElement> inline _EuclideanRingElement euclidean(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

struct Edge {
    int u, v;
    long long w;
    bool used, def;
    Edge(int u, int v, long long w, bool def) : u{ u }, v{ v }, w{ w }, used{ false }, def{ def } {}
    int other(int node) { return node == u ? v : u; }
    bool operator<(const Edge &that) const {
        return w == that.w ? def > that.def : w < that.w;
    }
};

int N, M, D, anc[17][100001], dsu[100001], depths[100001];
long long weights[17][100001], total_cost, min_cost, days;
Edge *edge_list[200000];
vector<Edge *> graph[100001];

int find_root(int node) { return dsu[node] == node ? node : dsu[node] = find_root(dsu[node]); }

void dfs(int node, int parent, long long weight, int depth) {
    anc[0][node] = parent;
    depths[node] = depth;
    weights[0][node] = weight;

    for (Edge *adj_edge : graph[node]) {
        int other = adj_edge->other(node);
        if (other == parent) continue;
        dfs(other, node, adj_edge->def ? 0 : adj_edge->w, depth + 1);
    }
}

void build_sparse_table() {
    for (int i = 1; i <= 16; i++) {
        for (int j = 1; j <= N; j++) {
            anc[i][j] = anc[i - 1][anc[i - 1][j]];
            weights[i][j] = max(weights[i - 1][j], weights[i - 1][anc[i - 1][j]]);
        }
    }
}

int get_lca(int u, int v) {
    if (depths[u] < depths[v]) swap(u, v);
    for (int i = 16; i >= 0; i--) {
        if (depths[u] - (1 << i) >= depths[v])
            u = anc[i][u];
        if (depths[u] == depths[v]) break;
    }
    if (u == v) return u;
    for (int i = 16; i >= 0; i--)
        if (anc[i][u] != anc[i][v])
            u = anc[i][u], v = anc[i][v];
    return anc[0][u];
}

long long get_up(int u, int v) {
    long long ret = -inf;
    for (int i = 16; i >= 0; i--)
        if (depths[u] - (1 << i) >= depths[v])
            ret = max(ret, weights[i][u]), u = anc[i][u];
    return ret;
}

long long get_max_weight(int u, int v) {
    int lca = get_lca(u, v);
    return max(get_up(u, lca), get_up(v, lca));
}

void kruskal() {
    sort(edge_list, edge_list + M, [] (Edge *a, Edge *b) -> bool{ return *a < *b; });
    long long most_expensive = 0;
    for (int i = 1; i <= N; i++) dsu[i] = i;
    for (int i = 0; i < M; i++) {
        int ru = find_root(edge_list[i]->u), rv = find_root(edge_list[i]->v);
        if (ru != rv) {
            dsu[ru] = rv;
            edge_list[i]->used = true;
            graph[edge_list[i]->u].push_back(edge_list[i]);
            graph[edge_list[i]->v].push_back(edge_list[i]);
            days += !edge_list[i]->def;
            total_cost += edge_list[i]->w;
            most_expensive = edge_list[i]->w;
        }
    }

    min_cost = total_cost - most_expensive + max(0ll, most_expensive - D);
    dfs(1, 0, 0, 0);
    build_sparse_table();

    for (int i = 0; i < M; i++) {
        if (!edge_list[i]->used && edge_list[i]->def) {
            long long cur_cost = total_cost - get_max_weight(edge_list[i]->u, edge_list[i]->v) + max(0ll, edge_list[i]->w - D);
            if (min_cost >= cur_cost) {
                days--;
                return;
            }
        }
    }
}

int main() {
    scan(N);
    scan(M);
    scan(D);
    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        scan(u);
        scan(v);
        scan(w);
        edge_list[i] = new Edge(u, v, w, i < N - 1);
    }
    kruskal();
    printf("%lld\n", days);
    return 0;
}