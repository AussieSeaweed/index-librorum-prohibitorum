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

int N, E, Q, low[100001], pre[100001], post[100001], ptr, anc[17][100001], depths[100001];
bool visited[100001], is_articulate[100001];
vector<int> graph[100001];

void dfs(int node, int parent, int depth) {
    visited[node] = true;
    pre[node] = low[node] = ptr++;
    anc[0][node] = parent;
    depths[node] = depth;
    int num_children = 0;
    bool articulate = false;

    for (int adj : graph[node]) {
        if (!visited[adj]) {
            dfs(adj, node, depth + 1);
            low[node] = min(low[node], low[adj]);
            num_children++;

            if (low[adj] >= pre[node])
                articulate = true;
        } else if (adj != parent) {
            low[node] = min(low[node], pre[adj]);
        }
    }

    is_articulate[node] = parent ? articulate : num_children > 1;
    post[node] = ptr++;
}

void build_sparse_table() {
    for (int i = 1; i < 17; i++) {
        for (int j = 1; j <= N; j++) {
            anc[i][j] = anc[i - 1][anc[i - 1][j]];
        }
    }
}

int right_under(int ancestor, int node) {
    for (int i = 16; i >= 0; i--) {
        if (depths[node] - (1 << i) > depths[ancestor]) {
            node = anc[i][node];
        }
    }
    return node;
}

int main() {
    scan(N);
    scan(E);

    while (E--) {
        int u, v;
        scan(u);
        scan(v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0, 0);
    build_sparse_table();

    scan(Q);

    while (Q--) {
        int t;
        scan(t);
        bool ans;

        if (t == 1) {
            int a, b, c, d;
            scan(a);
            scan(b);
            scan(c);
            scan(d);
            if (pre[c] > pre[d]) swap(c, d); // c is above d
            ans = low[d] <= pre[c] || (pre[d] <= pre[a] && pre[a] <= post[d]) == (pre[d] <= pre[b] && pre[b] <= post[d]);
        } else {
            int a, b, c;
            bool sb = false, sa = false;
            scan(a);
            scan(b);
            scan(c);
            if (pre[c] <= pre[a] && pre[a] <= post[c]) a = right_under(c, a), sa = true;
            if (pre[c] <= pre[b] && pre[b] <= post[c]) b = right_under(c, b), sb = true;
            ans = !is_articulate[c] || a == b || ((!sa || low[a] < pre[c]) && (!sb || low[b] < pre[c]));
        }

        printf(ans ? "yes\n" : "no\n");
    }
    return 0;
}