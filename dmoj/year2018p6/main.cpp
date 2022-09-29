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
template<typename _EuclideanRingElement> inline _EuclideanRingElement gcd(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
#define BLOCK_SIZE 316
using namespace std;

struct Query {
    int l, r, n, b, i;
    Query(int l, int r, int n, int i) : l{ l }, r{ r }, n{ n }, b{ l / BLOCK_SIZE }, i{ i } {}
    bool operator<(const Query &that) const {
        return b == that.b ? (b & 1 ? r > that.r : r < that.r) : b < that.b;
    }
};

multiset<int> values, differences;
int N, Q, c[50001], tour[100000], p, ans[50000], b[50001], e[50001], anc[16][50001], depths[50001];
bool seen[50001];
Query *queries[50000];
vector<int> graph[50001];

void dfs(int node, int parent, int depth) {
    depths[node] = depth;
    anc[0][node] = parent;
    tour[b[node] = p++] = node;

    for (int adj : graph[node]) {
        if (adj == parent) continue;
        dfs(adj, node, depth + 1);
    }

    tour[e[node] = p++] = node;
}

void build_sparse_table() {
    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= N; j++) {
            anc[i][j] = anc[i - 1][anc[i - 1][j]];
        }
    }
}

int get_lca(int u, int v) {
    if (depths[u] < depths[v]) swap(u, v);
    for (int i = 15; i >= 0 && depths[u] != depths[v]; i--) {
        if (depths[u] - (1 << i) >= depths[v]) {
            u = anc[i][u];
        }
    }

    if (u == v) return u;

    for (int i = 15; i >= 0; i--) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u], v = anc[i][v];
        }
    }

    return anc[0][u];
}

void insert(int v) {
    auto it = values.lower_bound(v);

    if (it != values.end() && it != values.begin()) {
        int r_val = *it, l_val = *--it;
        it++, differences.erase(differences.lower_bound(r_val - l_val));
    }

    if (it != values.end()) {
        differences.insert(*it - v);
    }

    if (it != values.begin()) {
        differences.insert(v - *--it);
    }

    values.insert(v);
}

void erase(int v) {
    auto it = values.lower_bound(v), tmp = it;
    ++tmp;

    if (tmp != values.end() && it != values.begin()) {
        int r_val = *tmp, l_val = *--it;
        it++, differences.insert(r_val - l_val);
    }

    if (tmp != values.end()) {
        differences.erase(differences.lower_bound(*tmp - v));
    }

    if (it != values.begin()) {
        differences.erase(differences.lower_bound(v - *--it));
    }

    values.erase(values.lower_bound(v));
}

void update(int i) {
    seen[tour[i]] = !seen[tour[i]];

    if (seen[tour[i]])
        insert(c[tour[i]]);
    else
        erase(c[tour[i]]);
}

void mo() {
    sort(queries, queries + Q, [] (Query *a, Query *b) -> bool { return *a < *b; });

    int l = 0, r = -1;

    for (int i = 0; i < Q; i++) {
        int ql = queries[i]->l, qr = queries[i]->r;

        while (l < ql) {
            update(l);
            l++;
        }

        while (r < qr) {
            r++;
            update(r);
        }

        while (l > ql) {
            l--;
            update(l);
        }

        while (r > qr) {
            update(r);
            r--;
        }

        if (queries[i]->n) insert(c[queries[i]->n]);
        ans[queries[i]->i] = *differences.begin();
        if (queries[i]->n) erase(c[queries[i]->n]);
    }
}

int main() {
    scan(N);
    scan(Q);

    for (int i = 1; i <= N; i++) scan(c[i]);

    for (int i = 1; i < N; i++) {
        int u, v;
        scan(u);
        scan(v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0, 0);
    build_sparse_table();

    for (int i = 0; i < Q; i++) {
        int u, v;
        scan(u);
        scan(v);

        if (b[u] > b[v]) swap(u, v);

        int lca = get_lca(u, v);

        if (u == lca) {
            queries[i] = new Query(b[u], b[v], 0, i);
        } else {
            queries[i] = new Query(e[u], b[v], lca, i);
        }
    }

    mo();

    for (int i = 0; i < Q; i++)
        printf("%d\n", ans[i]);

    return 0;
}