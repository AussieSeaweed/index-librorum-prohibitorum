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

struct Vector {
    int x, y;
    long long w;

    Vector() : x{}, y{}, w{} {}
    Vector(int x, int y, long long w) : x{ x }, y{ y }, w{ w } {}
} points[4000];

const int num_steps = 10000;
const double TAU = 2 * M_PI;
const double eps = 1e-9;
pair<double, long long> tmp[4000], comp[4000];

bool eq(double a, double b) { if (a > TAU) a -= TAU; if (b > TAU) b -= TAU; return a - eps <= b && b <= a + eps; }
long long range_sum(int i, int j) { if (j < i) return 0; else return comp[j].second - (i == 0 ? 0 : comp[i - 1].second); }

int N, M, C;
long long ans;

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(points[i].x);
        scan(points[i].y);
        scan(points[i].w);
    }

    for (int i = 0; i < N; i++) {
        int j, k;
        double theta, step;
        M = 0;

        for (j = 0; j < N; j++) {
            if (i == j) continue;
            long long dx = points[j].x - points[i].x, dy = points[j].y - points[i].y;
            theta = atan2(dy, dx);
            if (theta < 0) theta += TAU;
            tmp[M++] = { theta, points[j].w };
        }

        sort(tmp, tmp + M);

        C = 0;

        for (j = 0; j < M; j++) {
            theta = tmp[j].first;
            long long sum = tmp[j].second;

            while (j < M - 1 && eq(tmp[j].first, tmp[j + 1].first))
                sum += tmp[++j].second;

            comp[C++] = { theta, sum };
        }

        for (j = 1; j < C; j++)
            comp[j].second += comp[j - 1].second;

        long long l, r, m;

        for (theta = 0, step = M_PI / num_steps, j = 0, k = 0, l = r = m = 0; theta < M_PI; theta += step) {
            while (j < C && comp[j].first <= theta)
                j++;

            while (k < C && comp[k].first < theta + M_PI)
                k++;

            m = points[i].w + (j > 0 && eq(comp[j - 1].first, theta) ? range_sum(j - 1, j - 1) : 0) +
                                            (k < C && eq(comp[k].first, theta + M_PI) ? range_sum(k, k) : 0);
            l = range_sum(j, k - 1), r = comp[C - 1].second - l - m + points[i].w;
            ans = max(ans, max(l, r) + max(0ll, m));
        }

        for (j = k = 0, l = r = m = 0; j < C; j++) {
            if (comp[j].first >= M_PI) break;

            while (k < C && comp[k].first < comp[j].first + M_PI)
                k++;

            m = points[i].w + range_sum(j, j) + (k < C && eq(comp[k].first, comp[j].first + M_PI) ? range_sum(k, k) : 0);
            l = range_sum(j + 1, k - 1), r = comp[C - 1].second - l - m + points[i].w;
            ans = max(ans, max(l, r) + max(0ll, m));
        }

        for (j = k = C - 1, l = r = m = 0; j >= 0; j--) {
            if (comp[j].first < M_PI) break;

            while (k >= 0 && comp[k].first < comp[j].first - M_PI)
                k--;

            m = points[i].w + range_sum(j, j) + (k >= 0 && eq(comp[k].first, comp[j].first - M_PI) ? range_sum(k, k) : 0);
            l = range_sum(k + 1, j - 1), r = comp[C - 1].second - l - m + points[i].w;
            ans = max(ans, max(l, r) + max(0ll, m));
        }
    }

    printf("%lld\n", ans);

    return 0;
}