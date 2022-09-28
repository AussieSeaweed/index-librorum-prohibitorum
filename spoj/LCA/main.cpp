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
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

int N, Q, M, cnt[1001], root, depths[1001], tour[11][1999], ptr = 0, start[1001], flog2[2000];
vector<int> graph[1001];

void cache_flog2() {
    flog2[1] = 0;
    for (int i = 2; i <= 2 * N - 1; i++)
        flog2[i] = 1 + flog2[i >> 1];
}

int dfs(int node, int parent, int depth) {
    tour[0][start[node] = ptr++] = node;
    depths[node] = depth;

    for (int adj : graph[node]) {
        if (adj == parent) continue;
        dfs(adj, node, depth + 1);
        tour[0][ptr++] = node;
    }
}

void build_sparse_table() {
    for (int i = 1; i <= flog2[2 * N - 1]; i++) {
        for (int j = 0; j + (1 << i) - 1 < 2 * N - 1; j++) {
            tour[i][j] = depths[tour[i - 1][j]] < depths[tour[i - 1][j + (1 << (i - 1))]] ? tour[i - 1][j] : tour[i - 1][j + (1 << (i - 1))];
        }
    }
}

int get_lca(int u, int v) {
    if (start[u] > start[v]) swap(u, v);
    int i = flog2[start[v] - start[u] + 1];
    return depths[tour[i][start[u]]] < depths[tour[i][start[v] - (1 << i) + 1]] ? tour[i][start[u]] : tour[i][start[v] - (1 << i) + 1];
}

int main() {
    int T;
    scan(T);
    for (int t = 1; t <= T; t++) {
        scan(N);
        cache_flog2();
        for_each(graph, graph + N + 1, [] (vector<int> &vec) -> void { vec.clear(); });
        fill(cnt, cnt + N + 1, 0);

        for (int i = 1; i <= N; i++) {
            scan(M);
            while (M--) {
                int c;
                scan(c);
                cnt[c]++;
                graph[i].push_back(c);
            }
        }

        for (int i = 1; i <= N; i++)
            if (!cnt[i])
                root = i;

        ptr = 0;
        dfs(root, 0, 0);
        build_sparse_table();

        scan(Q);
        printf("Case %d:\n", t);
        while (Q--) {
            int u, v;
            scan(u);
            scan(v);
            printf("%d\n", get_lca(u, v));
        }
    }
    return 0;
}