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

int N, parents[50001], weights[50001], tour[50000], ptr, badchild[50001], badcnt[50001];
unordered_map<int, int> w_cnt[50001];
vector<pair<int, int>> graph[50001];
bool dp[50001];

void dfs(int node, int parent, int weight) {
    parents[node] = parent;
    weights[node] = weight;
    w_cnt[node][weight]++;
    dp[node] = true;

    for (pair<int, int> &adj_edge : graph[node]) {
        if (adj_edge.first == parent) continue;
        w_cnt[node][adj_edge.second]++;
        dfs(adj_edge.first, node, adj_edge.second);
        bool query = dp[adj_edge.first] && w_cnt[adj_edge.first][adj_edge.second] == 1;
        dp[node] &= query;
        if (!query)
            badcnt[node]++, badchild[node] = adj_edge.first;
    }

    tour[ptr++] = node;
}

int main() {
    scan(N);

    for (int i = 1; i < N; i++) {
        int u, v, w;
        scan(u);
        scan(v);
        scan(w);
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    dfs(1, 0, 0);

    for (int i = N - 1; i >= 0; i--) {
        int node = tour[i];
        if (node != 1) {
            bool query = (badcnt[parents[node]] == 0 || (badcnt[parents[node]] == 1 && badchild[parents[node]] == node)) && w_cnt[parents[node]][weights[node]] == 1;
            if (!query)
                badcnt[node]++, badchild[node] = parents[node];
            dp[node] &= query;
        }
    }

    printf("%d\n", count(dp + 1, dp + N + 1, true));

    for (int i = 1; i <= N; i++)
        if (dp[i])
            printf("%d\n", i);

    return 0;
}