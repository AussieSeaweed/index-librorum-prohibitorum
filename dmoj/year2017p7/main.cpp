#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> inline constexpr const T &_min(const T &x,const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x,const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x,const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x,const Ts &...xs) { return _max(x, _max(xs...)); }
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
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

vector<pair<long long, long long>> graph[100001];
long long N, C, takes[100001], delay[100001], depth[100001], b[100001], e[100001], euler_tour[200002], E = 0, anc[18][100001], current[524288], cnt[524288], last[100001];

void dfs(long long node, long long parent, long long d, long long t) {
    depth[node] = d;
    takes[node] = t;
    euler_tour[b[node] = E++] = node;
    anc[0][node] = parent;

    for (pair<long long, long long> &adj_edge : graph[node]) {
        dfs(adj_edge.first, node, d + 1, t + adj_edge.second);
    }

    euler_tour[e[node] = E++] = node;
}

void setup_sparse_table() {
    for (long long i = 1; i < 18; i++) {
        for (long long j = 0; j <= N; j++) {
            if (anc[i - 1][j] != -1) {
                anc[i][j] = anc[i - 1][anc[i - 1][j]];
            }
        }
    }
}

void setup_seg_tree(long long node, long long lo, long long hi) {
    if (lo == hi) {
        current[node] = depth[euler_tour[lo]];
    } else {
        long long mid = (lo + hi) / 2;
        setup_seg_tree(node * 2, lo, mid);
        setup_seg_tree(node * 2 + 1, mid + 1, hi);
        current[node] = max(current[node * 2], current[node * 2 + 1]);
    }
}

void update(long long node, long long lo, long long hi, long long left, long long right, long long delta) {
    if (right < lo || hi < left) return;
    if (left <= lo && hi <= right) {
        cnt[node] += delta;
    } else {
        long long mid = (lo + hi) / 2;
        update(node * 2, lo, mid, left, right, delta);
        update(node * 2 + 1, mid + 1, hi, left, right, delta);
        current[node] = max((cnt[node * 2] ? 0 : current[node * 2]), (cnt[node * 2 + 1] ? 0 : current[node * 2 + 1]));
    }
}

long long get_unworking_node(long long node) {
    long long d = delay[node];
    for (long long i = 17; i >= 0; i--) {
        if (anc[i][node] != -1 && takes[anc[i][node]] >= d) {
            node = anc[i][node];
        }
    }
    return node;
}

int main() {
    scan(N);
    for (long long i = 1; i <= N; i++) scan(delay[i]);

    for (long long i = 1; i <= N; i++) {
        long long parent, t;
        scan(parent);
        scan(t);
        graph[parent].emplace_back(i, t);
    }

    dfs(0, -1, 0, 0);
    setup_sparse_table();
    setup_seg_tree(1, 0, E - 1);

    for (long long i = 1; i <= N; i++) {
        if (delay[i] <= takes[i]) {
            long long node = last[i] = get_unworking_node(i);
            update(1, 0, E - 1, b[node], e[node], 1);
        } else {
            last[i] = -1;
        }
    }

    scan(C);

    while (C--) {
        long long node;
        scan(node);
        scan(delay[node]);

        if (~last[node]) {
            update(1, 0, E - 1, b[last[node]], e[last[node]], -1);
        }

        if (delay[node] <= takes[node]) {
            long long n = last[node] = get_unworking_node(node);
            update(1, 0, E - 1, b[n], e[n], 1);
        } else {
            last[node] = -1;
        }

        printf("%lld\n", current[1]);
    }

    return 0;
}