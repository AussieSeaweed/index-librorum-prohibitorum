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

struct Point { long long x, y; Point(long long x, long long y) : x{ x }, y{ y } {} } *points[50000];
long long N, min_v[16][50000], max_v[16][50000], total, min_area = INF;
int flog2[50001];

void cache_flog2() {
    flog2[1] = 0;
    for (int i = 2; i <= 50000; i++)
        flog2[i] = 1 + flog2[i / 2];
}

long long query_min(int i, int j) {
    int lvl = flog2[j - i + 1];
    return min(min_v[lvl][i], min_v[lvl][j - (1 << lvl) + 1]);
}

long long query_max(int i, int j) {
    int lvl = flog2[j - i + 1];
    return max(max_v[lvl][i], max_v[lvl][j - (1 << lvl) + 1]);
}

void store_y() {
    for (int i = 0; i < N; i++)
        min_v[0][i] = max_v[0][i] = points[i]->y;
    for (int i = 1; i <= 15; i++)
        for (int j = 0; j + (1 << i) - 1 < N; j++) {
            min_v[i][j] = min(min_v[i - 1][j], min_v[i - 1][j + (1 << (i - 1))]);
            max_v[i][j] = max(max_v[i - 1][j], max_v[i - 1][j + (1 << (i - 1))]);
        }
}

void get_total() {
    long long min_x = inf, max_x = -inf, min_y = inf, max_y = -inf;
    for (int i = 0; i < N; i++)
        min_x = min(min_x, points[i]->x), max_x = max(max_x, points[i]->x), min_y = min(min_y, points[i]->y), max_y = max(max_y, points[i]->y);
    total = (max_x - min_x) * (max_y - min_y);
}

bool intersects(long long a, long long b, long long c, long long d) {
    return (a <= c && c <= b) || (a <= d && d <= b) || (c <= a && a <= d) || (c <= b && b <= d);
}

void solve() {
    sort(points, points + N, [] (Point *a, Point *b) -> bool{ return a->x < b->x; });
    store_y();
    for (int i = 0; i < N - 1; i++) {
        if (points[i]->x == points[i + 1]->x && intersects(query_min(0, i), query_max(0, i), query_min(i + 1, N - 1), query_max(i + 1, N - 1))) continue;
        min_area = min(min_area, (query_max(0, i) - query_min(0, i)) * (points[i]->x - points[0]->x) + (query_max(i + 1, N - 1) - query_min(i + 1, N - 1)) * (points[N - 1]->x - points[i + 1]->x));
    }
}

int main() {
    scan(N);
    for (int i = 0; i < N; i++) {
        long long x, y;
        scan(x);
        scan(y);
        points[i] = new Point(x, y);
    }
    cache_flog2();
    get_total();
    solve();
    for (int i = 0; i < N; i++) swap(points[i]->x, points[i]->y);
    solve();
    printf("%lld\n", total - min_area);
    return 0;
}