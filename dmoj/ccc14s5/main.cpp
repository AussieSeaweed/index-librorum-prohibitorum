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
template<typename _EuclideanRingElement> inline _EuclideanRingElement gcd(_EuclideanRingElement _m, _EuclideanRingElement _n) { return __gcd(_m, _n); }
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
    int u, v, w;
    inline bool operator>(const Edge &that) const {
        return w > that.w;
    }
};

int N, E, dp[2001], pdp[2001], x[2001], y[2001], last_dist[2001], ans;
Edge edges[2001000];

inline int sqr_dist(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2, dy = y1 - y2;
    return dx * dx + dy * dy;
}

int main() {
    scan(N);
    for (int i = 1; i <= N; i++) {
        scan(x[i]);
        scan(y[i]);
    }

    for (int i = 0; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            edges[E].u = i, edges[E].v = j, edges[E].w = sqr_dist(x[i], y[i], x[j], y[j]);
            E++;
        }
    }

    sort(edges, edges + E, greater<Edge>());
    fill(last_dist, last_dist + N + 1, inf);
    fill(dp, dp + N + 1, -inf);
    dp[0] = 0;

    for (int i = 0; i < E; i++) {
        int &u = edges[i].u, &v = edges[i].v, &w = edges[i].w;

        if (w < last_dist[u]) {
            last_dist[u] = w;
            pdp[u] = dp[u];
        }

        if (w < last_dist[v]) {
            last_dist[v] = w;
            pdp[v] = dp[v];
        }

        dp[v] = max(dp[v], pdp[u] + 1);
        if (u) dp[u] = max(dp[u], pdp[v] + 1);

        ans = max(ans, dp[u], dp[v]);
    }

    printf("%d\n", ans);

    return 0;
}