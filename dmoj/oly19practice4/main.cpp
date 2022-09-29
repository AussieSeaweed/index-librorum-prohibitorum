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

struct Query {
    int t, a, b, c, i;
    Query(int t, int a, int b, int c = -1, int i = -1) : t{ t }, a{ a }, b{ b }, c{ c }, i{ i } {}
};

int N, M, a[200001], ans[200000], Q, bit[200001];
vector<Query *> queries;

void update(int i, int d) {
    while (i <= N) {
        bit[i] += d;
        i += i & -i;
    }
}

int query(int i) {
    int ret = 0;
    while (i) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

void solve(int lo, int hi, vector<Query *> &queries) {
    if (queries.empty()) return;

    if (lo == hi) {
        for (Query *q : queries)
            if (q->t == 2)
                ans[q->i] = lo;
    } else {
        int mid = (lo + hi) / 2;

        for (Query *q : queries) {
            if (q->t == 0 || q->t == 1) {
                if (q->b <= mid) update(q->a, q->t == 0 ? 1 : -1);
            } else {
                ans[q->i] = query(q->b) - query(q->a - 1);
            }
        }

        vector<Query *> l, r;

        for (Query *q : queries) {
            if (q->t == 0 || q->t == 1) {
                if (q->b <= mid) update(q->a, q->t == 0 ? -1 : 1), l.push_back(q);
                else r.push_back(q);
            } else {
                if (q->c <= ans[q->i]) l.push_back(q);
                else q->c -= ans[q->i], r.push_back(q);
            }
        }

        solve(lo, mid, l);
        solve(mid + 1, hi, r);
    }
}

int main() {
    scan(N);

    for (int i = 1; i <= N; i++) {
        scan(a[i]);
        queries.push_back(new Query(0, i, a[i]));
    }

    scan(M);

    for (int i = 0; i < M; i++) {
        int t;
        scan(t);
        if (t == 1) {
            int x;
            scan(x);
            queries.push_back(new Query(1, x, a[x]));
            scan(a[x]);
            queries.push_back(new Query(0, x, a[x]));
        } else {
            int x, y, k;
            scan(x);
            scan(y);
            scan(k);
            queries.push_back(new Query(2, x, y, k, Q++));
        }
    }

    solve(1, 1000000000, queries);

    for (int i = 0; i < Q; i++)
        printf("%d\n", ans[i]);

    return 0;
}