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
using namespace std;

struct Update {
    int par, child;
    Update(int par, int child) : par{ par }, child{ child } {}
};

vector<Update> updates;
vector<pair<int, int>> seg_tree[1048576];
pair<int, int> edge_list[200000];
int N, M, K, par[400000], sz[400000], num_connected_comps, ans[400000], lifetime[400000];

void init(int N) {
    for (int i = 0; i < N; i++) par[i] = i, sz[i] = 1;
    num_connected_comps = N;
}

int find_root(int node) { return par[node] == node ? node : find_root(par[node]); }

void join(int u, int v) {
    int ru = find_root(u), rv = find_root(v);

    if (ru != rv) {
        if (sz[ru] < sz[rv]) swap(ru, rv);
        par[rv] = ru;
        sz[ru] += sz[rv];
        updates.emplace_back(ru, rv);
        num_connected_comps--;
    } else {
        updates.emplace_back(-1, -1);
    }
}

void rollback() {
    Update update = updates.back();
    updates.pop_back();

    if (~update.par && ~update.child) {
        par[update.child] = update.child;
        sz[update.par] -= sz[update.child];
        num_connected_comps++;
    }
}

void add_edge(int node, int lo, int hi, int qlo, int qhi, const pair<int, int> &edge) {
    if (qhi < lo || hi < qlo) return;

    if (qlo <= lo && hi <= qhi) {
        seg_tree[node].push_back(edge);
    } else {
        int mid = (lo + hi) / 2;
        add_edge(node * 2, lo, mid, qlo, qhi, edge);
        add_edge(node * 2 + 1, mid + 1, hi, qlo, qhi, edge);
    }
}

void dfs(int node, int lo, int hi) {
    for (const pair<int, int> &edge : seg_tree[node])
        join(edge.first, edge.second);

    if (lo == hi) {
        ans[lo] = num_connected_comps - lo;
    } else {
        int mid = (lo + hi) / 2;
        dfs(node * 2, lo, mid);
        dfs(node * 2 + 1, mid + 1, hi);
    }

    for (const pair<int, int> &edge : seg_tree[node])
        rollback();
}

int main() {
    scan(N, M);

    for (int i = 0; i < M; i++)
        scan(edge_list[i].first, edge_list[i].second);

    scan(K);

    init(N);
    fill(lifetime, lifetime + N, K);

    for (int i = 0; i < K; i++) {
        int node;
        scan(node);
        lifetime[node] = i;
    }

    for (int i = 0; i < M; i++)
        add_edge(1, 0, K, 0, min(lifetime[edge_list[i].first], lifetime[edge_list[i].second]), edge_list[i]);

    dfs(1, 0, K);

    for (int i = 0; i <= K; i++)
        printf("%d\n", ans[i]);

    return 0;
}