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
#define MOD 1000000007
using namespace std;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u{ u }, v{ v }, w{ w } {}
    int other(int node) { return node == u ? v : u; }
};

int N, M, X, Y, n, anc[11][1500], depths[1500], dists[1500];
long long cnt[1500][2501], sum[1500][2501], scnt[1500][2501], ssum[1500][2501];
pair<long long, long long> dp[1501][2501];
set<int> pdists[1500];
vector<int> tree_nodes[1500];
bool visited[1500], vdp[1501][2501];
vector<Edge *> graph[1500];

void dfs(int node, int parent, int depth, int id, int dist) {
    depths[node] = depth;
    anc[0][node] = parent;
    dists[node] = dist;
    visited[node] = true;
    tree_nodes[id].push_back(node);

    for (Edge *edge : graph[node]) {
        int other = edge->other(node);
        if (visited[other]) continue;
        dfs(other, node, depth + 1, id, dist + edge->w);
    }
}

void build_sparse_table() {
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < N; j++) {
            anc[i][j] = ~anc[i - 1][j] ? anc[i - 1][anc[i - 1][j]] : -1;
        }
    }
}

int get_lca(int u, int v) {
    if (depths[u] < depths[v]) swap(u, v);

    for (int i = 10; i >= 0; i--) {
        if (depths[u] - (1 << i) >= depths[v])
            u = anc[i][u];
        if (depths[u] == depths[v]) break;
    }

    if (u == v) return u;

    for (int i = 10; i >= 0; i--)
        if (anc[i][u] != anc[i][v])
            u = anc[i][u], v = anc[i][v];

    return anc[0][u];
}

long long fact(int i) {
    return i == 0 ? 1 : i * fact(i - 1) % MOD;
}

long long pow(int base, int exp) {
    return exp == 0 ? 1 : base * pow(base, exp - 1) % MOD;
}

pair<long long, long long> solve(int i, int j) {
    if (vdp[i][j]) return dp[i][j];
    vdp[i][j] = true;
    if (i == n) return dp[i][j] = j == 0 ? make_pair(1, 0) : make_pair(0, 0);
    dp[i][j] = {0, 0};

    auto lim = pdists[i].lower_bound(j);

    for (auto it = pdists[i].begin(); it != lim; it++) {
        pair<long long, long long> query = solve(i + 1, j - *it);
        if (query.first) {
            query.second = (sum[i][*it] * query.first % MOD + cnt[i][*it] * query.second % MOD) % MOD;
            dp[i][j].second = (dp[i][j].second + query.second) % MOD;

            query.first = query.first * cnt[i][*it] % MOD;
            dp[i][j].first = (dp[i][j].first + query.first) % MOD;
        }
    }

    if (lim != pdists[i].end()) {
        pair<long long, long long> query = solve(i + 1, 0);
        if (query.first) {
            query.second = (ssum[i][*lim] * query.first % MOD + scnt[i][*lim] * query.second % MOD) % MOD;
            dp[i][j].second = (dp[i][j].second + query.second) % MOD;

            query.first = query.first * scnt[i][*lim] % MOD;
            dp[i][j].first = (dp[i][j].first + query.first) % MOD;
        }
    }

    return dp[i][j];
}

int main() {
    scan(N);
    scan(M);
    scan(X);
    scan(Y);

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scan(u);
        scan(v);
        scan(w);
        u--, v--;
        Edge *edge = new Edge(u, v, w);
        graph[u].push_back(edge);
        graph[v].push_back(edge);
    }

    for (int i = 0; i < N; i++)
        if (!visited[i])
            dfs(i, -1, 0, n++, 0);

    Y = max(0, Y - n * X);

    build_sparse_table();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < tree_nodes[i].size(); j++) {
            for (int k = j + 1; k < tree_nodes[i].size(); k++) {
                int u = tree_nodes[i][j], v = tree_nodes[i][k];
                int dist = dists[u] + dists[v] - 2 * dists[get_lca(u, v)];
                cnt[i][min(Y, dist)] = (cnt[i][min(Y, dist)] + 1) % MOD, sum[i][min(Y, dist)] = (sum[i][min(Y, dist)] + dist) % MOD, pdists[i].insert(min(Y, dist));
            }
        }
    }

    for (int i = 0; i < n; i++) {
        copy(cnt[i], cnt[i] + Y + 1, scnt[i]);
        copy(sum[i], sum[i] + Y + 1, ssum[i]);
        for (int j = Y - 1; j >= 0; j--) {
            scnt[i][j] = (scnt[i][j] + scnt[i][j + 1]) % MOD;
            ssum[i][j] = (ssum[i][j] + ssum[i][j + 1]) % MOD;
        }
    }

    memset(dp, -1, sizeof dp);
    auto ans = solve(0, Y);
    printf("%lld\n", fact(n - 1) * pow(2, n - 1) % MOD * ((ans.first * n * X + ans.second) % MOD) % MOD);

    return 0;
}