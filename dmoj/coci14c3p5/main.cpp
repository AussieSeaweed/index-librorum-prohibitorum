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
using namespace std;

struct Query {
    int u, v, i;
} queries[300000];

int N, Q, node[300001], ans[300001], anc[19][300001], depths[300001];

void build_sparse_table() {
    for (int i = 1; i < 19; i++) {
        for (int j = 0; j <= N; j++) {
            if (~anc[i - 1][j]) {
                anc[i][j] = anc[i - 1][anc[i - 1][j]];
            }
        }
    }
}

int get_lca(int u, int v) {
    if (depths[u] < depths[v]) swap(u, v);

    for (int i = 18; i >= 0; i--) {
        if (depths[u] - (1 << i) >= depths[v])
            u = anc[i][u];
        if (depths[u] == depths[v])
            break;
    }

    if (u == v) return u;

    for (int i = 18; i >= 0; i--)
        if (~anc[i][u] && ~anc[i][v] && anc[i][u] != anc[i][v])
            u = anc[i][u], v = anc[i][v];

    return anc[0][u];
}

int main() {
    scan(N);
    fill(ans, ans + N + 1, -1);
    fill(anc[0], anc[0] + N + 1, -1);

    for (int i = 1; i <= N; i++) {
        char t;
        int v, w;
        scanf(" %c", &t);
        scan(v);
        node[i] = node[v];

        if (t == 'a') {
            anc[0][i] = node[i];
            depths[i] = depths[node[i]] + 1;
            node[i] = i;
        } else if (t == 'b') {
            ans[i] = node[i];
            node[i] = anc[0][node[i]];
        } else {
            scan(w);
            queries[Q++] = {node[v], node[w], i};
        }
    }

    build_sparse_table();

    for (int i = 0; i < Q; i++) {
        ans[queries[i].i] = depths[get_lca(queries[i].u, queries[i].v)];
    }

    for (int i = 1; i <= N; i++) {
        if (~ans[i]) {
            printf("%d\n", ans[i]);
        }
    }

    return 0;
}