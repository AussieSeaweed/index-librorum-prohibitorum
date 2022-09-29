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
template<typename _EuclideanRingElement> inline _EuclideanRingElement euclidean(_EuclideanRingElement _m, _EuclideanRingElement _n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

int N, downnode[1000001], topo[1000000], ptr, parents[1000001], down[2][1000001], x[1000001];
pair<int, int> ans {1, 0};
vector<int> graph[1000001];

bool cmp(pair<int, int> a, pair<int, int> b) {
    return ((double) a.first) / a.second < ((double) b.first) / b.second;
}

int dfs(int node, int parent) {
    parents[node] = parent;
    int max_down = 0;

    for (int adj : graph[node]) {
        if (adj == parent) continue;
        int query = dfs(adj, node);
        max_down = max(max_down, query);
        if (down[0][node] < query) {
            down[1][node] = down[0][node];
            down[0][node] = query;
            downnode[node] = adj;
        } else if (down[1][node] < query) {
            down[1][node] = query;
        }
    }

    topo[ptr++] = node;
    return x[node] == 1 ? max_down + 1 : 0;
}

int main() {
    scan(N);

    for (int i = 1; i < N; i++) {
        int u, v;
        scan(u);
        scan(v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= N; i++) {
        scan(x[i]);
        if (cmp(make_pair(x[i], 1), ans))
            ans = make_pair(x[i], 1);
    }

    dfs(1, 0);

    for (int i = N - 1; i >= 0; i--) {
        int node = topo[i];

        if (parents[node]) {
            int query = x[parents[node]] == 1 ? (downnode[parents[node]] == node ? down[1][parents[node]] : down[0][parents[node]]) + 1 : 0;

            if (down[0][node] < query) {
                down[1][node] = down[0][node];
                down[0][node] = query;
                downnode[node] = parents[node];
            } else if (down[1][node] < query) {
                down[1][node] = query;
            }
        }

        if (x[node] <= 2) {
            if (cmp(make_pair(x[node], down[0][node] + down[1][node] + 1), ans))
                ans = make_pair(x[node], down[0][node] + down[1][node] + 1);
        }
    }
    int gcd = euclidean(ans.first, ans.second);
    ans.first /= gcd;
    ans.second /= gcd;
    printf("%d/%d\n", ans.first, ans.second);

    return 0;
}