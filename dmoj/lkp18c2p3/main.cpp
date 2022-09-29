#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
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
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

struct Point {
    long long x, y;
    Point() {}
    Point(long long x, long long y) : x{ x }, y{ y } {}
    bool operator==(const Point &that) const {
        return x == that.x && y == that.y;
    }
};

long long o(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

struct Triangle {
    Point a, b, c;
    Triangle(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) : a{ x1, y1 }, b{ x2, y2 }, c{ x3, y3 } {}
    bool contains(const Point &pt) const {
        if (a == b && b == c) {
            return pt == a;
        } else if (a == b) {
            return o(a, pt, c) == 0;
        } else if (b == c) {
            return o(a, pt, b) == 0;
        } else if (c == a) {
            return o(a, pt, b) == 0;
        } else {
            long long p = o(pt, a, b), q = o(pt, b, c), l = o(pt, c, a);
            bool pos = p > 0 || q > 0 || l > 0, neg = p < 0 || q < 0 || l < 0;
            return !(pos && neg);
        }
    }
};

Point points[100];
int N, M;

int main() {
    scan(N);
    scan(M);
    for (int i = 0; i < N; i++) { scan(points[i].x); scan(points[i].y); }
    while (M--) {
        long long x1, y1, x2, y2, x3, y3;
        scan(x1);
        scan(y1);
        scan(x2);
        scan(y2);
        scan(x3);
        scan(y3);
        Triangle triangle{ x1, y1, x2, y2, x3, y3 };
        int cnt = 0;
        for (int i = 0; i < N; i++)
            if (triangle.contains(points[i]))
                cnt++;
        printf("%d\n", cnt);
    }
    return 0;
}