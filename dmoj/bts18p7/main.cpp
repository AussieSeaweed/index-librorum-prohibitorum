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

struct Edge {
    int u, v, w;
    Edge(int u, int v) : u{ u }, v{ v }, w{ inf } {}
    int other(int node) { return node == v ? u : v; }
};

int N, Q, R, anc[17][100001], p[17][100001], s[17][100001], depth[100001];
Edge *edges[100000];
vector<Edge *> graph[100001];

void dfs(int node, int parent, int d) {
    anc[0][node] = parent;
    depth[node] = d;

    for (Edge *adj_edge : graph[node]) {
        int other = adj_edge->other(node);
        if (other == parent) continue;
        s[0][other] = adj_edge->w;
        dfs(other, node, d + 1);
    }
}

void build_sparse_tree() {
    for (int i = 1; i <= 16; i++) {
        for (int j = 1; j <= N; j++) {
            if (anc[i - 1][j]) {
                anc[i][j] = anc[i - 1][anc[i - 1][j]];
                p[i][j] = max(p[i - 1][j], p[i - 1][anc[i - 1][j]]);
                s[i][j] = min(s[i - 1][j], s[i - 1][anc[i - 1][j]]);
                string();
            }
        }
    }
}

int get_lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);

    for (int i = 16; i >= 0; i--) {
        if (depth[a] - (1 << i) >= depth[b]) {
            a = anc[i][a];
        }

        if (depth[a] == depth[b]) break;
    }

    if (a == b) return a;

    for (int i = 16; i >= 0; i--) {
        if (anc[i][a] != anc[i][b]) {
            a = anc[i][a];
            b = anc[i][b];
        }
    }

    return anc[0][a];
}

int get_min_destruction_time(int node, int ancestor) {
    int ret = inf;

    for (int i = 16; i >= 0; i--) {
        if (depth[node] - (1 << i) >= depth[ancestor]) {
            ret = min(ret, s[i][node]);
            node = anc[i][node];
        }
    }

    return ret;
}

int get_lowest_occurence_aux(int node, int lvl, int k) {
    if (lvl == 0) return node;
    return p[lvl - 1][node] >= k ? get_lowest_occurence_aux(node, lvl - 1, k) :
                                    get_lowest_occurence_aux(anc[lvl - 1][node], lvl - 1, k);
}

int get_lowest_occurence(int node, int ancestor, int k) {
    for (int i = 16; i >= 0; i--) {
        if (depth[node] - (1 << i) >= depth[ancestor]) {
            if (p[i][node] >= k)
                return get_lowest_occurence_aux(node, i, k);

            node = anc[i][node];
        }

        if (depth[node] == depth[ancestor]) break;
    }
    return -1;
}

int get_highest_occurence_aux(int node, int lvl, int k) {
    if (lvl == 0) return node;
    return p[lvl - 1][anc[lvl - 1][node]] >= k ? get_highest_occurence_aux(anc[lvl - 1][node], lvl - 1, k) :
                                                    get_highest_occurence_aux(node, lvl - 1, k);
}

int get_highest_occurence(int node, int ancestor, int k) {
    int q_node = 0, q_lvl = 0;
    for (int i = 16; i >= 0; i--) {
        if (depth[node] - (1 << i) >= depth[ancestor]) {
            if (p[i][node] >= k)
                q_node = node, q_lvl = i;

            node = anc[i][node];
        }

        if (depth[node] == depth[ancestor]) break;
    }
    return q_node ? get_highest_occurence_aux(q_node, q_lvl, k) : -1;
}

int solve(int a, int b, int k, int t) {
    int lca = get_lca(a, b);
    if (min(get_min_destruction_time(a, lca), get_min_destruction_time(b, lca)) < t) return -1;
    int ql = get_lowest_occurence(a, lca, k);
    return ~ql ? ql : (p[0][lca] >= k ? lca : get_highest_occurence(b, lca, k));
}

int main() {
    scan(N);
    scan(Q);
    scan(R);

    for (int i = 1; i <= N; i++) scan(p[0][i]);

    for (int i = 1; i < N; i++) {
        int u, v;
        scan(u);
        scan(v);
        edges[i] = new Edge(u, v);
        graph[u].push_back(edges[i]);
        graph[v].push_back(edges[i]);
    }

    for (int i = 0; i < R; i++) {
        int x, y;
        scan(x);
        scan(y);
        edges[y]->w = x;
    }

    s[0][1] = inf;
    dfs(1, 0, 0);
    build_sparse_tree();

    for (int i = 1; i <= Q; i++) {
        int a, b, k;
        scan(a);
        scan(b);
        scan(k);
        printf("%d\n", solve(a, b, k, i));
    }

    return 0;
}