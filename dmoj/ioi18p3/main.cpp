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

vector<int> min_tree[200000], max_tree[200000];
int N, M, Q, n, min_begin[200000], min_end[200000], max_begin[200000], max_end[200000], e, dsu[200000], min_anc[18][200000], max_anc[18][200000], bit[200001];
pair<int, int> edges[400000];

void setup_dsu() {
    for (int i = 0; i < N; i++)
        dsu[i] = i;
}

int find_root(int node) { return node == dsu[node] ? node : dsu[node] = find_root(dsu[node]); }

void dfs(int node, int parent, vector<int> graph[], int euler_begin[], int euler_end[], int anc[][200000]) {
    euler_begin[node] = e++;
    anc[0][node] = parent;

    for (int adj : graph[node]) {
        if (adj == parent) continue;
        dfs(adj, node, graph, euler_begin, euler_end, anc);
    }

    euler_end[node] = e++;
}

void build_sparse_table(int anc[][200000]) {
    for (int i = 1; i < 18; i++) {
        for (int j = 0; j < N; j++) {
            if (~anc[i - 1][j]) {
                anc[i][j] = anc[i - 1][anc[i - 1][j]];
            } else {
                anc[i][j] = -1;
            }
        }
    }
}

int anc_he(int node, int L) {
    for (int i = 17; i >= 0; i--) {
        if (~max_anc[i][node] && max_anc[i][node] >= L) {
            node = max_anc[i][node];
        }
    }
    return node;
}

int anc_le(int node, int R) {
    for (int i = 17; i >= 0; i--) {
        if (~min_anc[i][node] && min_anc[i][node] <= R) {
            node = min_anc[i][node];
        }
    }
    return node;
}

struct Event {
    int x, y1, y2, t, i;
    bool operator<(const Event &that) const { return x == that.x ? t < that.t : x < that.x; }
} events[600000];

int query(int i) {
    int ret = 0;
    i++;

    while (i) {
        ret += bit[i];
        i -= i & -i;
    }

    return ret;
}

void update(int i) {
    i++;

    while (i <= e) {
        bit[i]++;
        i += i & -i;
    }
}

void solve(vector<int> &S, vector<int> &E, vector<int> &L, vector<int> &R, vector<int> &ans) {
    for (int i = 0; i < N; i++)
        events[n].x = max_begin[i], events[n].y1 = min_begin[i], events[n].t = 1, n++;

    for (int i = 0; i < Q; i++) {
        int node_he = anc_he(S[i], L[i]), node_le = anc_le(E[i], R[i]);

        events[n].x = max_begin[node_he];
        events[n].y1 = min_begin[node_le];
        events[n].y2 = min_end[node_le];
        events[n].t = 0;
        events[n].i = i;
        n++;

        events[n].x = max_end[node_he];
        events[n].y1 = min_begin[node_le];
        events[n].y2 = min_end[node_le];
        events[n].t = 2;
        events[n].i = i;
        n++;
    }

    sort(events, events + n);

    for (int i = 0; i < n; i++) {
        Event &e = events[i];

        if (e.t == 0) {
            ans[e.i] = query(e.y2) - query(e.y1 - 1);
        } else if (e.t == 1) {
            update(e.y1);
        } else {
            ans[e.i] = (query(e.y2) - query(e.y1 - 1) - ans[e.i]) > 0;
        }
    }
}

vector<int> check_validity(int N, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R) {
    ::N = N;
    M = X.size();
    Q = S.size();

    for (int i = 0; i < M; i++)
        edges[i] = { X[i], Y[i] };

    setup_dsu();

    sort(edges, edges + M, [] (const pair<int, int> &a, const pair<int, int> &b) -> bool { return max(a.first, a.second) < max(b.first, b.second); });

    for (int i = 0; i < M; i++) {
        int u = min(edges[i].first, edges[i].second), v = max(edges[i].first, edges[i].second);
        int ru = find_root(u);

        if (ru != v) {
            min_tree[ru].push_back(v);
            min_tree[v].push_back(ru);
            dsu[ru] = v;
        }
    }

    setup_dsu();

    sort(edges, edges + M, [] (const pair<int, int> &a, const pair<int, int> &b) -> bool { return min(a.first, a.second) > min(b.first, b.second); });

    for (int i = 0; i < M; i++) {
        int u = max(edges[i].first, edges[i].second), v = min(edges[i].first, edges[i].second);
        int ru = find_root(u);

        if (ru != v) {
            max_tree[v].push_back(ru);
            max_tree[ru].push_back(v);
            dsu[ru] = v;
        }
    }

    dfs(N - 1, -1, min_tree, min_begin, min_end, min_anc);
    build_sparse_table(min_anc);

    e = 0;
    dfs(0, -1, max_tree, max_begin, max_end, max_anc);
    build_sparse_table(max_anc);

    vector<int> ans(Q);
    solve(S, E, L, R, ans);

    return ans;
}

int main() {
    
    return 0;
}