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

int N, Q, Y, E, bit[600001], ans[200000];
unordered_map<long long, int> compy;
long long y_values[600000];

struct Event {
    int t, v;
    long long x, ylo, yhi;
    bool operator<(const Event &that) const { return x == that.x ? t < that.t : x < that.x; }
} events[600000];

void update(int i, int v) {
    while (i <= 600000) {
        bit[i] += v;
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

void get_range(long long v, long long &lo, long long &hi) { // ignores most sig bit
    lo = 0, hi = 1ll << 61;
    for (int i = 0; i <= 60 && v != 1; i++, v >>= 1) {
        long long mid = lo + (hi - lo) / 2;

        if (v & 1) hi = mid;
        else lo = mid;
    }
    hi--;
}

long long get_exact(long long v) {
    long long lo = 0, hi = 1ll << 61;
    for (int i = 0; i <= 60; i++, v >>= 1) {
        long long mid = lo + (hi - lo) / 2;

        if (v & 1) hi = mid;
        else lo = mid;
    }
    return lo;
}

int main() {
    scan(N); scan(Q);

    for (int i = 0; i < N; i++) {
        long long x, y; int v;
        scan(x); scan(y); scan(v);
        long long xlo, xhi, ylo, yhi;
        get_range(x, xlo, xhi), get_range(y, ylo, yhi);
        y_values[Y++] = ylo, y_values[Y++] = yhi;
        events[E++] = {0, v, xlo, ylo, yhi}, events[E++] = {1, -v, xhi, ylo, yhi};
    }

    for (int i = 0; i < Q; i++) {
        long long x, y;
        scan(x);
        scan(y);
        x = get_exact(x), y = get_exact(y);
        y_values[Y++] = y;
        events[E++] = {2, i, x, y, 0};
    }

    sort(events, events + E);
    sort(y_values, y_values + Y);
    Y = unique(y_values, y_values + Y) - y_values;

    for (int i = 0; i < Y; i++)
        compy[y_values[i]] = i + 1;

    for (int i = 0; i < E; i++) {
        Event &e = events[i];

        if (e.t == 2) {
            ans[events[i].v] = query(compy[events[i].ylo]);
        } else {
            update(compy[events[i].ylo], events[i].v), update(compy[events[i].yhi], -events[i].v);
        }
    }

    for (int i = 0; i < Q; i++)
        printf("%d\n", ans[i]);

    return 0;
}