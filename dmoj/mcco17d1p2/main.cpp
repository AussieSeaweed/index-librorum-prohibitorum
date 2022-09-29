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

int N, K, Q;
long long seg_tree[524288], lazy[524288];

void handle_lazy(int node, int lo, int hi) {
    if (lazy[node]) {
        seg_tree[node]  += lazy[node];

        if (lo != hi) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }

        lazy[node] = 0;
    }
}

void update_range(int node, int lo, int hi, int left, int right, long long delta) {
    handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return;
    if (left <= lo && hi <= right) {
        lazy[node] += delta;
        handle_lazy(node, lo, hi);
    } else {
        int mid = (lo + hi) / 2;
        update_range(node * 2, lo, mid, left, right, delta);
        update_range(node * 2 + 1, mid + 1, hi, left, right, delta);
        seg_tree[node] = max(seg_tree[node * 2], seg_tree[node * 2 + 1]);
    }
}

long long query(int node, int lo, int hi, int left, int right) {
    handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return 0;
    else if (left <= lo && hi <= right) return seg_tree[node];

    int mid = (lo + hi) / 2;
    return max(query(node * 2, lo, mid, left, right), query(node * 2 + 1, mid + 1, hi, left, right));
}

int main() {
    scan(N);
    scan(K);
    scan(Q);
    while (Q--) {
        int t, a, b;
        scan(t);
        scan(a);
        scan(b);
        if (t == 1) {
            printf("%lld\n", query(1, 0, N, a, b));
        } else {
            update_range(1, 0, N, a - K + 1, a, b);
        }
    }
    return 0;
}