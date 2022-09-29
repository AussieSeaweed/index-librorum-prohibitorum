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
    int u, v, last_num;
    Edge(int u, int v) : u{ u }, v{ v }, last_num{ 0 } {}
};

struct Update {
    int u, v;
    Edge *edge;
    Update(int u, int v, Edge *edge) : u{ u }, v{ v }, edge{ edge } {}
};

stack<Update> updates;
stack<int> states;
vector<Edge *> query_tree[524288];
int N, M, Q, uf[100001], sz[100001], num[100001], t[100000];
Edge *edge_list[100000];

inline void init() {
    for (int i = 1; i <= N; i++) uf[i] = i, sz[i] = num[i] = 1;
}

inline int find_root(int node) {
    while (node != uf[node])
        node = uf[node];
    return node;
}

inline void merge(Edge *edge) {
    int ru = find_root(edge->u), rv = find_root(edge->v);

    if (sz[ru] < sz[rv]) swap(ru, rv); // ru is root

    uf[rv] = ru;
    sz[ru] += sz[rv];
    num[ru] += num[rv] - edge->last_num;
    updates.emplace(ru, rv, edge);
}

inline void undo() {
    Update update = updates.top();
    updates.pop();

    update.edge->last_num = num[update.v] = num[update.u];
    sz[update.u] -= sz[update.v];
    uf[update.v] = update.v;
}

inline void save_state() {
    states.push(updates.size());
}

inline void restore_state() {
    while (updates.size() > states.top()) {
        undo();
    }

    states.pop();
}

void add_query(int node, int lo, int hi, int left, int right, Edge *edge) {
    if (right < lo || hi < left) return;
    if (left <= lo && hi <= right) {
        query_tree[node].push_back(edge);
    } else {
        int mid = (lo + hi) / 2;
        add_query(node * 2, lo, mid, left, right, edge);
        add_query(node * 2 + 1, mid + 1, hi, left, right, edge);
    }
}

void dfs(int node, int lo, int hi) {
    save_state();

    for (Edge *edge : query_tree[node])
        merge(edge);

    if (lo != hi) {
        int mid = lo + (hi - lo) / 2;
        dfs(node * 2, lo, mid);
        dfs(node * 2 + 1, mid + 1, hi);
    }

    restore_state();
}

int main() {
    pscan(N);
    pscan(M);
    pscan(Q);

    for (int i = 1; i < N; i++) {
        int u, v;
        pscan(u);
        pscan(v);
        edge_list[i] = new Edge(u, v);
    }

    fill(t, t + N, -1);

    for (int i = 0; i < M; i++) {
        int d;
        pscan(d);
        if (~t[d]) {
            add_query(1, 0, M, t[d], i, edge_list[d]);
            t[d] = -1;
        } else {
            t[d] = i;
        }
    }

    for (int i = 1; i < N; i++) {
        if (~t[i]) {
            add_query(1, 0, M, t[i], M, edge_list[i]);
        }
    }

    init();
    dfs(1, 0, M);

    while (Q--) {
        int c;
        pscan(c);
        printf("%d\n", num[c]);
    }

    return 0;
}