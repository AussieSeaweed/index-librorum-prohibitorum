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

struct Node {
    long long sum = 0, value = 0;
    int cnt = 0;
} seg_tree[262144];
int N, M, K, hld_index[100001], sparse_table[18][199999], e_index[100001], ptr, parents[100001], depths[100001], head[100001], heavy[100001], flog2[200000];
bool is_crucial[100001];
long long base_array[100000], values[100001];
set<int> active;
vector<pair<int, long long>> graph[100001];
pair<int, int> edge_list[100001];

int dfs(int node, int parent, int depth, long long value) {
    depths[node] = depth;
    parents[node] = parent;
    sparse_table[0][e_index[node] = ptr++] = node;
    values[node] = value;
    int size = 1, max_query = 0;

    for (pair<int, long long> &adj_edge : graph[node]) {
        if (adj_edge.first == parent) continue;
        int query = dfs(adj_edge.first, node, depth + 1, adj_edge.second);
        size += query;
        if (query > max_query)
            max_query = query, heavy[node] = adj_edge.first;
        sparse_table[0][ptr++] = node;
    }

    return size;
}

void decompose(int node, int cur_head) {
    head[node] = cur_head;
    base_array[hld_index[node] = ptr++] = values[node];

    if (heavy[node])
        decompose(heavy[node], cur_head);

    for (pair<int, long long> &adj_edge : graph[node]) {
        if (adj_edge.first == parents[node] || adj_edge.first == heavy[node]) continue;
        decompose(adj_edge.first, adj_edge.first);
    }
}

void cache_flog2() {
    flog2[1] = 0;
    for (int i = 2; i <= 2 * N - 1; i++)
        flog2[i] = 1 + flog2[i / 2];
}

void build_sparse_table() {
    int lim = 2 * N - 1;
    for (int i = 1; i < 18; i++) {
        for (int j = 0; j + (1 << i) - 1 < lim; j++) {
            sparse_table[i][j] = depths[sparse_table[i - 1][j]] < depths[sparse_table[i - 1][j + (1 << (i - 1))]] ?
                                 sparse_table[i - 1][j] : sparse_table[i - 1][j + (1 << (i - 1))];
        }
    }
}

int query_min(int i, int j) {
    int level = flog2[j - i + 1];
    return depths[sparse_table[level][i]] < depths[sparse_table[level][j - (1 << level) + 1]] ?
           sparse_table[level][i] : sparse_table[level][j - (1 << level) + 1];
}

void build_seg_tree(int node, int lo, int hi) {
    if (lo == hi) {
        seg_tree[node].sum = base_array[lo];
    } else {
        int mid = (lo + hi) / 2;
        build_seg_tree(node * 2, lo, mid);
        build_seg_tree(node * 2 + 1, mid + 1, hi);
        seg_tree[node].sum = seg_tree[node * 2].sum + seg_tree[node * 2 + 1].sum;
    }
}

void update_range(int node, int lo, int hi, int left, int right, int delta) {
    if (right < lo || hi < left) return;
    if (left <= lo && hi <= right) {
        seg_tree[node].cnt += delta;
    } else {
        int mid = (lo + hi) / 2;
        update_range(node * 2, lo, mid, left, right, delta);
        update_range(node * 2 + 1, mid + 1, hi, left, right, delta);
        seg_tree[node].value = (seg_tree[node * 2].cnt ? seg_tree[node * 2].sum : seg_tree[node * 2].value) +
                               (seg_tree[node * 2 + 1].cnt ? seg_tree[node * 2 + 1].sum : seg_tree[node * 2 + 1].value);
    }
}

void update(int node, int lo, int hi, int index, int value) {
    if (index < lo || hi < index) return;
    if (lo == hi) {
        seg_tree[node].sum = value;
    } else {
        int mid = (lo + hi) / 2;
        update(node * 2, lo, mid, index, value);
        update(node * 2 + 1, mid + 1, hi, index, value);
        seg_tree[node].sum = seg_tree[node * 2].sum + seg_tree[node * 2 + 1].sum;
        seg_tree[node].value = (seg_tree[node * 2].cnt ? seg_tree[node * 2].sum : seg_tree[node * 2].value) +
                               (seg_tree[node * 2 + 1].cnt ? seg_tree[node * 2 + 1].sum : seg_tree[node * 2 + 1].value);
    }
}

long long query(int node, int lo, int hi, int left, int right) {
    if (right < lo || hi < left) return 0;
    if (left <= lo && hi <= right) return seg_tree[node].sum;
    int mid = (lo + hi) / 2;
    return query(node * 2, lo, mid, left, right) + query(node * 2 + 1, mid + 1, hi, left, right);
}

long long query_all() {
    return seg_tree[1].cnt ? seg_tree[1].sum : seg_tree[1].value;
}

void hld_update(int node, int delta) {
    for (; ~node; node = parents[head[node]]) {
        update_range(1, 0, N - 1, hld_index[head[node]], hld_index[node], delta);
    }
}

long long hld_query(int node) {
    long long ret = 0;

    for (; ~node; node = parents[head[node]]) {
        ret += query(1, 0, N - 1, hld_index[head[node]], hld_index[node]);
    }

    return ret;
}

int main() {
    scan(N);
    scan(M);
    scan(K);

    for (int i = 0; i < K; i++) {
        int node;
        scan(node);
        is_crucial[node] = true;
    }

    for (int i = 1; i < N; i++) {
        long long w;
        scan(edge_list[i].first);
        scan(edge_list[i].second);
        scan(w);
        graph[edge_list[i].second].emplace_back(edge_list[i].first, w);
        graph[edge_list[i].first].emplace_back(edge_list[i].second, w);
    }

    cache_flog2();
    dfs(1, -1, 0, 0);
    ptr = 0;
    decompose(1, 1);
    build_sparse_table();
    build_seg_tree(1, 0, N - 1);

    for (int i = 1; i <= N; i++) {
        if (is_crucial[i]) {
            active.insert(e_index[i]);
            hld_update(i, 1);
        }
    }

    int global_lca = query_min(*active.begin(), *active.rbegin());
    printf("%lld\n", query_all() - hld_query(global_lca));

    while (M--) {
        int t;
        scan(t);

        switch (t) {
            case 1: {
                int c;
                scan(c);
                is_crucial[c] = !is_crucial[c];
                hld_update(c, is_crucial[c] ? 1 : -1);
                if (is_crucial[c])
                    active.insert(e_index[c]);
                else
                    active.erase(e_index[c]);
                global_lca = query_min(*active.begin(), *active.rbegin());
            }
                break;
            default: {
                int r, u;
                scan(r);
                scan(u);
                int node = depths[edge_list[r].first] > depths[edge_list[r].second] ?
                           edge_list[r].first : edge_list[r].second;
                update(1, 0, N - 1, hld_index[node], u);
            }
                break;
        }

        printf("%lld\n", query_all() - hld_query(global_lca));
    }

    return 0;
}