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

unordered_set<pair<long long, long long>, pair_hash> coords;
pair<long long, long long> points[1500], others[1499];
int N, n;
long long ans = 0;
double eps = 1e-8;

long long cross(pair<long long, long long> &a, pair<long long, long long> &b) {
    return a.first * b.second - a.second * b.first;
}

long long dot(pair<long long, long long> &a, pair<long long, long long> &b) {
    return a.first * b.first + a.second * b.second;
}

double angle_btw(double a, double b) {
    if (a - eps <= b && b <= a + eps)
        return 0;
    else if (b > a)
        return b - a;
    else
        return 2 * M_PI - (a - b);
}

int main() {
    scan(N);
    n = N - 1;

    for (int i = 0; i < N; i++) {
        scan(points[i].first, points[i].second);
        coords.insert(points[i]);
    }

    for (int i = 0; i < N; i++) {
        copy(points, points + i, others), copy(points + i + 1, points + N, others + i);
        for_each(others, others + n, [&] (pair<long long, long long> &pt) -> void { pt.first -= points[i].first, pt.second -= points[i].second; });
        sort(others, others + n, [] (pair<long long, long long> &a, pair<long long, long long> &b) -> bool { return cross(a, b) > 0; });

        for (int j = 0, k = 0; j < n; j++) {
            while (dot(others[j], others[k]) > 0 && (k + 1) % n != j)
                k = (k + 1) % n;

            if (dot(others[j], others[k]) == 0 && coords.count({points[i].first + others[j].first + others[k].first,
                    points[i].second + others[j].second + others[k].second})) {
                ans = max(ans, cross(others[j], others[k]));
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}