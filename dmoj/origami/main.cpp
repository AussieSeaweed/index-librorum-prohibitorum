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
    long long x, y;
    Vector operator-(const Vector &that) const { return {x - that.x, y - that.y}; }
    double length() const { return hypot(x, y); }
    Vector rot90() const { return {-y, x}; }
} points[100000], hull[100000];

long long dot(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y;
}

double sproj(const Vector &v, const Vector &onto) {
    return dot(v, onto) / onto.length();
}

long long cross(const Vector &a, const Vector &b) {
    return a.x * b.y - a.y * b.x;
}

int N, M;
double ans;

void graham_scan() {
    int min_index = -1;
    long long min_y = INF;

    for (int i = 0; i < N; i++)
        if (points[i].y < min_y)
            min_y = points[i].y, min_index = i;

    swap(points[0], points[min_index]);

    sort(points + 1, points + N, [] (const Vector &a, const Vector &b) -> bool {
        long long o = cross(a - points[0], b - points[0]);
        return o == 0 ? (a - points[0]).length() < (b - points[0]).length() : o > 0;
    });

    hull[0] = points[0], hull[1] = points[1], M = 2;

    for (int i = 2; i < N; i++) {
        if (cross(hull[M - 1] - hull[M - 2], points[i] - hull[M - 2]) == 0) {
            hull[M - 1] = points[i];
            continue;
        }

        while (cross(hull[M - 1] - hull[M - 2], points[i] - hull[M - 2]) < 0)
            M--;

        hull[M++] = points[i];
    }
}

int get_leftmost() {
    int min_index = -1;
    long long min_x = INF;

    for (int i = 0; i < M; i++)
        if (hull[i].x < min_x)
            min_x = hull[i].x, min_index = i;

    return min_index;
}

int get_rightmost() {
    int max_index = -1;
    long long max_x = -INF;

    for (int i = 0; i < M; i++)
        if (hull[i].x > max_x)
            max_x = hull[i].x, max_index = i;

    return max_index;
}

int get_topmost() {
    int max_index = -1;
    long long max_y = -INF;

    for (int i = 0; i < M; i++)
        if (hull[i].y > max_y)
            max_y = hull[i].y, max_index = i;

    return max_index;
}

void rotating_calipers() {
    ans = INFINITY;

    int l = get_leftmost(), r = get_rightmost(), t = get_topmost();

    for (int i = 0; i < M; i++) {
        int j = (i + 1) % M;
        Vector lv = hull[i] - hull[j], rv = hull[j] - hull[i], tv = rv.rot90();
        int nl = (l + 1) % M, nr = (r + 1) % M, nt = (t + 1) % M;

        while (sproj(hull[nl] - hull[i], lv) > sproj(hull[l] - hull[i], lv))
            l = nl, nl = (l + 1) % M;

        while (sproj(hull[nr] - hull[j], rv) > sproj(hull[r] - hull[j], rv))
            r = nr, nr = (r + 1) % M;

        while (sproj(hull[nt] - hull[j], tv) > sproj(hull[t] - hull[j], tv))
            t = nt, nt = (t + 1) % M;

        ans = min(ans, (lv.length() + sproj(hull[l] - hull[i], lv) + sproj(hull[r] - hull[j], rv)) *
                       sproj(hull[t] - hull[j], tv));
    }
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(points[i].x);
        scan(points[i].y);
    }

    graham_scan();
    rotating_calipers();

    printf("%.0lf\n", ans);
    return 0;
}