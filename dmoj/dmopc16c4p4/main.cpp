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
#define K 316
using namespace std;

int N, Q, a[100000], cnt[100001], ans[100000], cur;
struct Query {
    int l, r, b, i;
    bool operator<(const Query &that) const { return b == that.b ? (b & 1 ? r > that.r : r < that.r) : b < that.b; }
} queries[100000];

void solve() {
    sort(queries, queries + Q);

    int l = 0, r = -1;
    for (int i = 0; i < Q; i++) {
        Query &query = queries[i];

        while (l < query.l) {
            if (cnt[a[l]] && cnt[a[l]] % 2 == 0) cur--;
            cnt[a[l]]--;
            if (cnt[a[l]] && cnt[a[l]] % 2 == 0) cur++;
            l++;
        }

        while (r < query.r) {
            if (cnt[a[r + 1]] && cnt[a[r + 1]] % 2 == 0) cur--;
            cnt[a[r + 1]]++;
            if (cnt[a[r + 1]] && cnt[a[r + 1]] % 2 == 0) cur++;
            r++;
        }

        while (l > query.l) {
            if (cnt[a[l - 1]] && cnt[a[l - 1]] % 2 == 0) cur--;
            cnt[a[l - 1]]++;
            if (cnt[a[l - 1]] && cnt[a[l - 1]] % 2 == 0) cur++;
            l--;
        }

        while (r > query.r) {
            if (cnt[a[r]] && cnt[a[r]] % 2 == 0) cur--;
            cnt[a[r]]--;
            if (cnt[a[r]] && cnt[a[r]] % 2 == 0) cur++;
            r--;
        }

        ans[query.i] = cur;
    }
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++)
        scan(a[i]);

    scan(Q);

    for (int i = 0; i < Q; i++) {
        scan(queries[i].l, queries[i].r);
        queries[i].l--, queries[i].r--;
        queries[i].b = queries[i].l / K;
        queries[i].i = i;
    }

    solve();

    for (int i = 0; i < Q; i++)
        printf("%d\n", ans[i]);

    return 0;
}