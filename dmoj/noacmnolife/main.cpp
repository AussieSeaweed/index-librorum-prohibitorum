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

int T, N, K, values[301], dists[301][301], parents[301][301], unique_cnt[301][301];
bool visited[301][301];
double bcdp[301][301];
vector<int> graph[301];

double bc(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (visited[n][k]) return bcdp[n][k];
    visited[n][k] = true;
    if (k == 0 || k == n) return bcdp[n][k] = 1;
    return bcdp[n][k] = bc(n - 1, k - 1) + bc(n - 1, k);
}

void dfs(int node, int parent, int source, int dist, unordered_map<int, int> &cnt) {
    dists[source][node] = dist;
    parents[source][node] = parent;
    cnt[values[node]]++;
    unique_cnt[source][node] = cnt.size();

    for (int adj : graph[node]) {
        if (adj == parent) continue;
        dfs(adj, node, source, dist + 1, cnt);
    }

    cnt[values[node]]--;
    if (cnt[values[node]] == 0) cnt.erase(values[node]);
}

inline void traverse_all() {
    unordered_map<int, int> cnt;
    for (int i = 1; i <= N; i++)
        dfs(i, 0, i, 0, cnt);
}

inline double solve() {
    double exp = 0;
    traverse_all();
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            int diameter_dist = dists[i][j], subtree_size = 0;
            for (int k = 1; k <= N; k++) {
                if (k == i || k == j)
                    subtree_size++;
                else if (max(dists[i][k], dists[j][k]) < diameter_dist)
                    subtree_size++;
                else if (dists[i][k] == diameter_dist && max(dists[i][k], dists[j][k]) == diameter_dist && k > j)
                    subtree_size++;
                else if (dists[j][k] == diameter_dist && dists[i][k] < diameter_dist && k > i)
                    subtree_size++;
            }
            exp += bc(subtree_size - 2, K - 2) / bc(N, K) * unique_cnt[i][j];
        }
    }
    return exp;
}

int main() {
    scan(T);
    while (T--) {
        scan(N);
        scan(K);
        for_each(graph, graph + N + 1, [] (vector<int> &vec) -> void { vec.clear(); });
        for (int i = 1; i < N; i++) {
            int u, v;
            scan(u);
            scan(v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        for (int i = 1; i <= N; i++) scan(values[i]);
        printf("%.10lf\n", solve());
    }
    return 0;
}