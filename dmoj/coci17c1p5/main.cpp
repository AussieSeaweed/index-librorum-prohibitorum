#include <bits/stdc++.h>
#include <bits/extc++.h>
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
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
template<typename T> inline void scan(T &x) { char c; bool sign; while ((x = getchar()) < '-'); sign = x == '-'; if (sign) while ((x = getchar()) < '0'); for(x -= '0'; '0' <= (c = getchar()); x = (x << 3) + (x << 1) + c - '0'); x = sign ? -x : x; }
template<typename T, typename ...Ts> inline void scan(T &x, Ts &...xs) { scan(x), scan(xs...); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;


struct Query {
    int t, x, a, i;
    Query(int t, int x, int a, int i = -1) : t{ t }, x{ x }, a{ a }, i{ i } {}
};

int N, Q, q, tmp[100001], ans[200000], shift_ind, size;
vector<Query> queries;

void init(int shift_ind, int size) {
    fill(tmp, tmp + size + 1, inf);
    ::shift_ind = shift_ind, ::size = size;
}

int inv(int i) {
    return size - i - 1;
}

void update(int i, int value) {
    i = inv(max(0, i - shift_ind)) + 1;

    while (i <= size) {
        tmp[i] = min(tmp[i], value);
        i += i & -i;
    }
}

int query(int i) {
    i = inv(max(0, i - shift_ind)) + 1;
    int ret = inf;

    while (i) {
        ret = min(ret, tmp[i]);
        i -= i & -i;
    }

    return ret;
}

void solve(int lo, int hi, vector<Query> &queries) {
    if (lo == hi) {
        int min_stops = inf;

        for (Query &q : queries) {
            if (q.t == 1) {
                assert(lo == q.a);
                min_stops = q.x;
            } else {
                if (min_stops <= q.x) ans[q.i] = lo;
            }
        }
    } else {
        int mid = (lo + hi) / 2;
        init(lo, mid - lo + 1);

        vector<Query> left, right;

        for (Query &q : queries) {
            if (q.t == 1) {
                if (lo <= q.a && q.a <= mid) {
                    left.push_back(q);
                    update(q.a, q.x);
                } else {
                    right.push_back(q);
                }
            } else {
                if (mid < q.a || q.x < query(q.a)) {
                    right.push_back(q);
                } else {
                    left.push_back(q);
                }
            }
        }

        solve(lo, mid, left);
        solve(mid + 1, hi, right);
    }
}

int main() {
    scan(N, Q);

    for (int i = 0; i < Q; i++) {
        char t;
        scanf(" %c", &t);

        if (t == 'M') {
            int x, a;
            scan(x, a);
            queries.emplace_back(1, x, a - 1);
        } else {
            int y, b;
            scan(y, b);
            queries.emplace_back(2, y, b - 1, q++);
        }
    }

    fill(ans, ans + q, -1);
    solve(0, N - 1, queries);

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i] == -1 ? -1 : ans[i] + 1);

    return 0;
}