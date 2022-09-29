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

struct Edge {
    int to;
    Edge *next_edge;
    bool used;
    Edge(int to, Edge *next_edge) : to{ to }, next_edge{ next_edge }, used{ false } {}
};

int N, Q, ans[100001], tmp[100001], k[100001], n;
unordered_map<int, int> ind[100001];
vector<int> graph[100001];
vector<bool> visited[100001];

void update(int node) {
    if (!~tmp[node]) tmp[node] = n;
    ans[node] = max(ans[node], n - tmp[node]);
    tmp[node] = n;
}

void update(int node, int i) {
    int src = node, src_i = i, num_cycled = 0;
    n = 0;

    do {
        update(node);
        visited[node][i] = true;
        n++;
        int next_node = graph[node][i];
        int next_i = (ind[next_node][node] - 1 + k[next_node]) % k[next_node];
        node = next_node;
        i = next_i;
        if (node == src && i == src_i)
            num_cycled++;
    } while (num_cycled < 2);
}

int main() {
    scan(N);

    for (int i = 1; i <= N; i++) {
        scan(k[i]);
        graph[i].resize(k[i]);
        visited[i].resize(k[i]);

        for (int j = 0; j < k[i]; j++)
            scan(graph[i][j]);

        for (int j = 0; j < k[i]; j++)
            ind[i][graph[i][j]] = j;
    }

    fill(tmp, tmp + N + 1, -1);

    for (int i = 1; i <= N; i++)
        for (int j = 0; j < k[i]; j++)
            if (!visited[i][j])
                update(i, j);

    scan(Q);

    while (Q--) {
        int node;
        scan(node);
        printf("%d\n", ans[node]);
    }

    return 0;
}