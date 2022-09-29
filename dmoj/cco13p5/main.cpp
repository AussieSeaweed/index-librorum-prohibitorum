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

struct Point {
    double x, y;
} earth[500000], super[500000];

int T, N, failure[500000];
triple<double, double, int> pattern[500000], base[1000000];

bool equal(double a, double b) {
    return a - 1e-6 <= b && b <= a + 1e-6;
}

bool equal(triple<double, double, int> &a, triple<double, double, int> &b) {
    return equal(a.first, b.first) && equal(a.second, b.second) && a.third == b.third;
}

inline void init() {
    failure[0] = 0;

    for (int i = 1, j = 0; i < N;) {
        if (equal(pattern[i], pattern[j]))
            failure[i++] = ++j;
        else if (j > 0)
            j = failure[j - 1];
        else
            failure[i++] = 0;
    }
}

inline int kmp() {
    init();

    for (int i = 0, j = 0; i < 2 * N;) {
        if (equal(base[i], pattern[j])) {
            if (j + 1 == N)
                return i - j;
            else
                i++, j++;
        } else if (j > 0)
            j = failure[j - 1];
        else
            i++;
    }

    return -1;
}

inline double get_angle(const Point &a, const Point &b, const Point &c) {
    double a1 = atan2(a.y - b.y, a.x - b.x), a2 = atan2(c.y - b.y, c.x - b.x), delta;
    if (a1 < 0) a1 += 2 * M_PI;
    if (a2 < 0) a2 += 2 * M_PI;
    delta = max(a1, a2) - min(a1, a2);
    return min(delta, 2 * M_PI - delta);
}

inline double get_dist_ratio(const Point &a, const Point &b, const Point &c) {
    double d1 = hypot(b.x - a.x, b.y - a.y), d2 = hypot(c.x - b.x, c.y - b.y);
    return d1 / d2;
}

inline int get_orientation(const Point &a, const Point &b, const Point &c) {
    double o = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return equal(o, 0.0) ? 0 : (o < 0 ? -1 : 1);
}

inline void get_data(Point pts[], triple<double, double, int> data[]) {
    for (int i = 0; i < N; i++)
        data[i] = { get_angle(pts[i], pts[(i + 1) % N], pts[(i + 2) % N]), get_dist_ratio(pts[i], pts[(i + 1) % N], pts[(i + 2) % N]), get_orientation(pts[i], pts[(i + 1) % N], pts[(i + 2) % N]) };
}

int main() {
    int T;
    scan(T);
    while (T--) {
        scan(N);

        for (int i = 0; i < N; i++)
            scanf("%lf%lf", &earth[i].x, &earth[i].y);

        for (int i = 0; i < N; i++)
            scanf("%lf%lf", &super[i].x, &super[i].y);

        get_data(earth, pattern), get_data(super, base);
        copy(base, base + N, base + N);

        printf("%d\n", kmp() + 1);
    }
    return 0;
}