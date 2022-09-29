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

struct Query {
    int t, a, b, i;
    long long k;
    Query(int t, int a, int b, long long k, int i = -1) : t{ t }, a{ a }, b{ b }, k{ k }, i{ i } {}
};

int N, M, Q;
long long bit1[200001], bit2[200001], ans[200000], min_value = INF, max_value = -INF;
vector<Query *> queries;

void update(int i, long long delta, long long bit[]) {
    while (i <= N) {
        bit[i] += delta;
        i += i & -i;
    }
}

long long query(int i, long long bit[]) {
    long long ret = 0;
    while (i) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

void update(int l, int r, long long delta) {
    update(l, delta, bit1);
    update(r + 1, -delta, bit1);
    update(l, (l - 1) * delta, bit2);
    update(r + 1, -r * delta, bit2);
}

long long query(int i) {
    return i * query(i, bit1) - query(i, bit2);
}

void solve(long long lo, long long hi, vector<Query *> &queries) {
    if (queries.empty()) return;

    if (lo == hi) {
        for (Query *q : queries)
            if (q->t == 2)
                ans[q->i] = lo;
    } else {
        long long mid = lo + (hi - lo) / 2;

        for (Query *q : queries) {
            if (q->t == 1) {
                if (q->k > mid) update(q->a, q->b, 1);
            } else {
                ans[q->i] = query(q->b) - query(q->a - 1);
            }
        }

        vector<Query *> l, r;

        for (Query *q : queries) {
            if (q->t == 1) {
                if (q->k > mid) update(q->a, q->b, -1), r.push_back(q);
                else l.push_back(q);
            } else {
                if (q->k <= ans[q->i]) r.push_back(q);
                else q->k -= ans[q->i], l.push_back(q);
            }
        }

        solve(lo, mid, l);
        solve(mid + 1, hi, r);
    }
}

int main() {
    scan(N);
    scan(M);

    for (int i = 0; i < M; i++) {
        int t, a, b;
        long long k;
        scan(t);
        scan(a);
        scan(b);
        scan(k);
        if (t == 1) {
            queries.push_back(new Query(t, a, b, k));
            min_value = min(min_value, k);
            max_value = max(max_value, k);
        } else {
            queries.push_back(new Query(t, a, b, k, Q++));
        }
    }

    solve(min_value, max_value, queries);

    for (int i = 0; i < Q; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}