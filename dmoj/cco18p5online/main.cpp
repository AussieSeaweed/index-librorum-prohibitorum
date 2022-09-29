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
template<typename _EuclideanRingElement> inline _EuclideanRingElement euclidean(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

int N, K, Q, a[1000001], ans[1000000], seg_tree[2097152], prev_ans;
priority_queue<int> answers, erased;

inline int merge(int i, int j) {
    return a[i] == a[j] ? max(i, j) : (a[i] > a[j] ? i : j);
}

inline void build_seg_tree() {
    for (int i = 0; i < N; i++) seg_tree[i + N] = i;
    for (int i = N - 1; i >= 1; i--) seg_tree[i] = merge(seg_tree[2 * i], seg_tree[2 * i + 1]);
}

inline void update(int i) {
    for (i += N; i > 1; i /= 2)
        seg_tree[i / 2] = merge(seg_tree[i], seg_tree[i ^ 1]);
}

inline int query(int l, int r) {
    int ret = N;
    for (l += N, r += N; l <= r; l = (l + 1) / 2, r = (r - 1) / 2) {
        if (l & 1)
            ret = merge(ret, seg_tree[l]);
        if (!(r & 1))
            ret = merge(ret, seg_tree[r]);
    }
    return ret;
}

inline void update_ans(int i) {
    if (i == N) return;
    int l = query(max(0, i - K + 1), i - 1), r = query(i + 1, min(N - 1, i + K - 1));
    if (ans[i]) erased.push(ans[i]);
    ans[i] = a[i] >= a[l] && a[i] > a[r] ? a[i] + max(a[l], a[r]) : 0;
    if (ans[i]) answers.push(ans[i]);
}

int main() {
    scan(N);
    scan(K);
    scan(Q);
    a[N] = -1;
    for (int i = 0; i < N; i++) scan(a[i]);
    build_seg_tree();
    for (int i = 0; i < N; i++) update_ans(i);
    printf("%d\n", prev_ans = answers.empty() ? 0 : answers.top());
    while (Q--) {
        int i;
        scan(i); i = (i ^ prev_ans) - 1;
        scan(a[i]); a[i] ^= prev_ans;
        update(i);
        int l = query(max(0, i - K + 1), i - 1), r = query(i + 1, min(N - 1, i + K - 1));
        if (a[i] >= a[l] && a[i] > a[r])
            update_ans(i);
        else {
            update_ans(i);
            update_ans(l);
            update_ans(r);
        }
        while (!erased.empty() && answers.top() == erased.top()) answers.pop(), erased.pop();
        printf("%d\n", prev_ans = answers.empty() ? 0 : answers.top());
    }
    return 0;
}