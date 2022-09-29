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

int N, Q, a[100000], seg_tree[262144], make_same[262144];

inline void handle_lazy(int node, int lo, int hi) {
    if (~make_same[node]) {
        seg_tree[node] = make_same[node] * (hi - lo + 1);

        if (lo != hi) {
            make_same[node * 2] = make_same[node];
            make_same[node * 2 + 1] = make_same[node];
        }

        make_same[node] = -1;
    }
}

void build_seg_tree(int node, int lo, int hi) {
    make_same[node] = -1;

    if (lo == hi) {
        seg_tree[node] = 1;
    } else {
        int mid = (lo + hi) / 2;
        build_seg_tree(node * 2, lo, mid);
        build_seg_tree(node * 2 + 1, mid + 1, hi);
        seg_tree[node] = seg_tree[node * 2] + seg_tree[node * 2 + 1];
    }
}

void update(int node, int lo, int hi, int qlo, int qhi, int v) {
    handle_lazy(node, lo, hi);
    if (qhi < lo || hi <  qlo) return;

    if (qlo <= lo && hi <= qhi) {
        make_same[node] = v;
        handle_lazy(node, lo, hi);
    } else {
        int mid = (lo + hi) / 2;
        update(node * 2, lo, mid, qlo, qhi, v);
        update(node * 2 + 1, mid + 1, hi, qlo, qhi, v);
        seg_tree[node] = seg_tree[node * 2] + seg_tree[node * 2 + 1];
    }
}

int query(int node, int lo, int hi, int qlo, int qhi) {
    handle_lazy(node, lo, hi);
    if (qhi < lo || hi < qlo) return 0;
    if (qlo <= lo && hi <= qhi) return seg_tree[node];
    int mid = (lo + hi) / 2;
    return query(node * 2, lo, mid, qlo, qhi) + query(node * 2 + 1, mid + 1, hi, qlo, qhi);
}

int binary_search_begin(int i, int n) {
    int lo = i, hi = N;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (query(1, 0, N - 1, i, mid) <= n) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int get_num_since(int i) {
    return query(1, 0, N - 1, i, N - 1);
}

int get_total_num() {
    return get_num_since(0);
}

void init_ssum() {
    for (int i = 1; i < N; i++)
        a[i] += a[i - 1];
}

int get_sum(int begin, int end) {
    return a[end] - (begin == 0 ? 0 : a[begin - 1]);
}

int main() {
    scan(N);
    scan(Q);

    for (int i = 0; i < N; i++)
        scan(a[i]);

    init_ssum();
    build_seg_tree(1, 0, N - 1);

    while (Q--) {
        int t;
        scan(t);

        if (t == 1) {
            int i, k;
            scan(i);
            scan(k);
            i--, i %= get_total_num();
            i = binary_search_begin(0, i);
            k--, k %= get_num_since(i);
            k = binary_search_begin(i, k + 1) - 1;
            update(1, 0, N - 1, i + 1, k, 0);
        } else if (t == 2) {
            int i, k;
            scan(i);
            i--, i %= get_total_num();
            i = binary_search_begin(0, i);
            k = binary_search_begin(i, 1) - 1;
            update(1, 0, N - 1, i, k, 1);
        } else {
            int i, k;
            scan(i);
            scan(k);
            i--, i %= get_total_num();
            i = binary_search_begin(0, i);
            k--, k %= get_num_since(i);
            k = binary_search_begin(i, k + 1) - 1;
            printf("%d\n", get_sum(i, k));
        }
    }

    return 0;
}