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

int N, K, Q, st1[2097152], st2[2097152], ans[1000000], qualities[1000001];

int merge(int i, int j, int vals[]) {
    return vals[i] > vals[j] ? i : j;
}

void build(int node, int lo, int hi, int st[], int vals[]) {
    if (lo == hi) {
        st[node] = lo;
    } else {
        int mid = (lo + hi) / 2;
        build(node * 2, lo, mid, st, vals);
        build(node * 2 + 1, mid + 1, hi, st, vals);
        st[node] = merge(st[node * 2], st[node * 2 + 1], vals);
    }
}

void update(int node, int lo, int hi, int i, int val, int st[], int vals[]) {
    if (i < lo || hi < i) return;

    if (lo == hi) {
        vals[lo] = val;
    } else {
        int mid = (lo + hi) / 2;
        update(node * 2, lo, mid, i, val, st, vals);
        update(node * 2 + 1, mid + 1, hi, i, val, st, vals);
        st[node] = merge(st[node * 2], st[node * 2 + 1], vals);
    }
}

int query(int node, int lo, int hi, int qlo, int qhi, int st[], int vals[]) {
    if (qhi < lo || hi < qlo) return N;
    else if (qlo <= lo && hi <= qhi) return st[node];
    int mid = (lo + hi) / 2;
    return merge(query(node * 2, lo, mid, qlo, qhi, st, vals), query(node * 2 + 1, mid + 1, hi, qlo, qhi, st, vals), vals);
}

void update(int i) {
    if (i == N) return;
    int l = query(1, 0, N - 1, i - K + 1, i - 1, st1, qualities), r = query(1, 0, N - 1, i + 1, i + K - 1, st1, qualities);

    if (qualities[l] <= qualities[i] && qualities[i] > qualities[r])
        update(1, 0, N - 1, i, qualities[i] + max(qualities[l], qualities[r]), st2, ans);
    else
        update(1, 0, N - 1, i, 0, st2, ans);
}

int main() {
    scan(N);
    scan(K);
    scan(Q);

    for (int i = 0; i < N; i++)
        scan(qualities[i]);

    build(1, 0, N - 1, st1, qualities);
    build(1, 0, N - 1, st2, ans);

    for (int i = 0; i < N; i++)
        update(i);

    printf("%d\n", ans[st2[1]]);

    while (Q--) {
        int i, x;
        scan(i);
        scan(x);
        i--;
        update(1, 0, N - 1, i, x, st1, qualities);
        int l = query(1, 0, N - 1, i - K + 1, i - 1, st1, qualities), r = query(1, 0, N - 1, i + 1, i + K - 1, st1, qualities);
        update(i);
        update(l);
        update(r);
        printf("%d\n", ans[st2[1]]);
    }

    return 0;
}