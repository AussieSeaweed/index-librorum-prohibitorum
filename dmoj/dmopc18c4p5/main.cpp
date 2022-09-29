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

struct Edge {
    int u, v, w;
    bool is_sm;
    Edge(int u, int v, int w, bool is_sm) : u{ u }, v{ v }, w{ w }, is_sm{ is_sm } {}
    int other(int node) { return node == u ? v : u; }
};

int N, K, dp[200001][3], topo[200000], ptr, parents[200001], ans, ret[200001], down[200001][2], downnode[200001];
vector<pair<int, int>> values[200001];
bool is_sm[200000];
Edge *edge_list[200000], *edge_to[200000];
vector<Edge *> graph[200001];

int solve(int i, int j, vector<pair<int, int>> &values) {
    if (j == 3) return -inf;
    if (~dp[i][j]) return dp[i][j];
    if (i == values.size()) return dp[i][j] = 0;
    return dp[i][j] = max(values[i].first + solve(i + 1, j + 1, values), values[i].second + solve(i + 1, j, values));
}

int solve(vector<pair<int, int>> &values) {
    for (int i = 0; i <= values.size(); i++)
        fill(dp[i], dp[i] + 3, -1);
    return solve(0, 0, values);
}

void dfs(int node, int parent) {
    parents[node] = parent;

    for (Edge *adj_edge : graph[node]) {
        if (adj_edge->other(node) == parent) continue;
        edge_to[adj_edge->other(node)] = adj_edge;
        dfs(adj_edge->other(node), node);
    }

    topo[ptr++] = node;
}

int main() {
    scan(N);
    scan(K);
    while (K--) { int s; scan(s); is_sm[s] = true; }
    for (int i = 1; i < N; i++) {
        int u, v, w;
        scan(u);
        scan(v);
        scan(w);
        edge_list[i] = new Edge(u, v, w, is_sm[i]);
        graph[u].push_back(edge_list[i]);
        graph[v].push_back(edge_list[i]);
    }

    dfs(1, 0);

    for (int i = 0; i < N; i++) {
        int node = topo[i];

        for (Edge *adj_edge : graph[node]) {
            int other = adj_edge->other(node);
            if (other == parents[node]) continue;
            ret[node] += adj_edge->is_sm ? 2 * adj_edge->w + ret[other] : 0;
        }

        for (Edge *adj_edge : graph[node]) {
            int other = adj_edge->other(node);
            if (other == parents[node]) continue;
            values[node].emplace_back(adj_edge->w + max(ret[other], down[other][0]), adj_edge->is_sm ? 2 * adj_edge->w + ret[other] : 0);

            int cur = ret[node] + values[node].back().first - values[node].back().second;
            if (cur > down[node][0]) {
                down[node][1] = down[node][0];
                down[node][0] = cur;
                downnode[node] = other;
            } else if (cur > down[node][1]) {
                down[node][1] = cur;
            }
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        int node = topo[i];

        if (node != 1) {
            int cur_down = edge_to[node]->w + max(ret[parents[node]], downnode[parents[node]] != node ? down[parents[node]][0] : down[parents[node]][1]) -
                            (edge_to[node]->is_sm ? 2 * edge_to[node]->w + ret[node] : 0);
            int cur_ret = edge_to[node]->is_sm ? ret[parents[node]] - ret[node] : 0;
            ret[node] += cur_ret;
            values[node].emplace_back(cur_down, cur_ret);

            int cur = ret[node] + values[node].back().first - values[node].back().second;
            if (cur > down[node][0]) {
                down[node][1] = down[node][0];
                down[node][0] = cur;
                downnode[node] = parents[node];
            } else if (cur > down[node][1]) {
                down[node][1] = cur;
            }
        }

        ans = max(ans, solve(values[node]));
    }

    printf("%d\n", ans);

    return 0;
}