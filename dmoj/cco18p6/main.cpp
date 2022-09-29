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

int N, values[4096];
vector<pair<int, int>> q1, q2;

inline void reverse(int lo, int hi, vector<pair<int, int>> &queries) {
    while (lo < hi) {
        swap(values[lo], values[hi]);
        queries.emplace_back(lo++, hi--);
    }
}

inline void merge(int lo, int mid, int hi, vector<pair<int, int>> &queries) {
    if (lo == hi || mid > hi || mid <= lo) return;

    int num = mid - lo, tl = lo, tm = mid;

    for (int i = 0; i < num; i++) {
        if (tl == mid)
            abort();
        else if (tm == hi + 1 || values[tl] < values[tm])
            tl++;
        else
            tm++;
    }

    reverse(tl, mid - 1, queries);
    reverse(mid, tm - 1, queries);
    reverse(tl, tm - 1, queries);
    merge(lo, tl, mid - 1, queries);
    merge(mid, tm, hi, queries);
}

inline void sort(int lo, int hi, vector<pair<int, int>> &queries) {
    if (lo == hi) return;
    int mid = (lo + hi) / 2;
    sort(lo, mid, queries), sort(mid + 1, hi, queries);
    merge(lo, mid + 1, hi, queries);
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++)
        scan(values[i]);

    sort(0, N - 1, q1);

    for (int i = 0; i < N; i++)
        scan(values[i]);

    sort(0, N - 1, q2);

    printf("%d\n", q1.size() + q2.size());

    for (pair<int, int> &op : q1)
        printf("%d %d\n", op.first + 1, op.second + 1);

    for (pair<int, int> &op : vector<pair<int, int>>(q2.rbegin(), q2.rend()))
        printf("%d %d\n", op.first + 1, op.second + 1);

    return 0;
}