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
template<typename _EuclideanRingElement> inline _EuclideanRingElement gcd(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
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
#define bsz 500
using namespace std;

struct Edge {
    int u, v, w;
    bool marked, used;
    Edge(int u, int v, int w) : u{ u }, v{ v }, w{ w }, marked{}, used{} {}
    inline bool operator<(const Edge &that) const { return w < that.w; }
} *edges[50000], *sedges[50000];

struct WEIGHT_ORDER {
    inline bool operator()(Edge * const &a, Edge * const &b) const { return *a < *b; }
};

int N, M, Q, q, n, num_full_blocks, dsu[50000], dsu_small[bsz + 1], id[50000], sz[50000], sz_small[bsz + 1];
long long ans[bsz];
pair<int, int> queries[bsz];

inline void init(int N, int dsu[], int sz[]) { for (int i = 0; i < N; i++) dsu[i] = i, sz[i] = 0; }
int find_root(int i, int dsu[]) { return dsu[i] == i ? i : dsu[i] = find_root(dsu[i], dsu); }
inline bool merge(int u, int v, int dsu[], int sz[]) {
    int ru = find_root(u, dsu), rv = find_root(v, dsu);
    if (ru != rv) { if (sz[ru] > sz[rv]) swap(ru, rv); dsu[ru] = rv, sz[rv] += sz[ru]; return true; }
    else return false;
}

inline void get_num_nodes() {
    n = 0;

    for (int i = 0; i < N; i++)
        if (dsu[i] == i) id[i] = n++;

    for (int i = 0; i < N; i++)
        id[i] = id[find_root(i, dsu)];
}

inline void solve() {
    for (int i = 0; i < q; i++) edges[queries[i].first]->marked = true;
    sort(sedges, sedges + M, [] (Edge * const &a, Edge * const &b) -> bool { return a->marked == b->marked ? *a < *b : a->marked > b->marked; });
    init(N, dsu, sz);

    long long base_ans = 0;

    for (int i = 0; i < M; i++) {
        sedges[i]->used = merge(sedges[i]->u, sedges[i]->v, dsu, sz);

        if (sedges[i]->used && !sedges[i]->marked)
            base_ans += sedges[i]->w;
    }

    init(N, dsu, sz);

    for (int i = 0; i < M; i++)
        if (sedges[i]->used && !sedges[i]->marked)
            merge(sedges[i]->u, sedges[i]->v, dsu, sz);

    get_num_nodes();
    vector<Edge *> pool;

    for (int i = 0; i < M; i++)
        if (sedges[i]->marked || (!sedges[i]->used && merge(sedges[i]->u, sedges[i]->v, dsu, sz)))
            pool.push_back(sedges[i]);

    for (int i = 0; i < q; i++) {
        edges[queries[i].first]->w = queries[i].second;
        sort(pool.begin(), pool.end(), [] (Edge * const &a, Edge * const &b) -> bool { return *a < *b; });
        init(n, dsu_small, sz_small);

        long long cur_ans = 0;

        for (Edge *edge : pool) {
            int u = id[edge->u], v = id[edge->v];
            if (merge(u, v, dsu_small, sz_small)) cur_ans += edge->w;
        }

        ans[i] = base_ans + cur_ans;
    }

    for_each(edges, edges + M, [] (Edge *&edge) -> void { edge->marked = edge->used = false; });
}

int main() {
    scan(N, M, Q);
    num_full_blocks = Q / bsz;

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scan(u, v, w);
        u--, v--;
        sedges[i] = edges[i] = new Edge(u, v, w);
    }

    for (int i = 0; i < num_full_blocks; i++) {
        q = bsz;

        for (int j = 0; j < q; j++)
            scan(queries[j].first, queries[j].second), queries[j].first--;

        solve();

        for (int j = 0; j < q; j++)
            printf("%lld\n", ans[j]);
    }

    q = Q - num_full_blocks * bsz;

    for (int i = 0; i < q; i++)
        scan(queries[i].first, queries[i].second), queries[i].first--;

    solve();

    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}