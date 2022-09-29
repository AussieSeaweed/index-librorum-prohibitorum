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
template<typename T> inline T gcd(const T &x, const T &y) { return std::__gcd(x, y); }
template<typename T, typename ...Ts> inline T gcd(const T &x, const Ts &...xs) { return std::__gcd(x, gcd(xs...)); }
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

double cache[1000001], dp[1000001], K;
int N, k, cnt[1000001];

struct Func {
    int a;
    double b;
    Func(int a, double b) : a{ a }, b{ b } {}

    double operator()(int x) {
        return cache[x - a] + b;
    }

    bool is_inferior_to(Func that) {
        return a > that.a && b <= that(a);
    }

    int overtaken(Func overtaker) {
        int lo = a, hi = N + 1;

        while (lo < hi) {
            int mid = (lo + hi) / 2;

            if ((*this)(mid) >= overtaker(mid)) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        return hi;
    }
};

vector<Func> hulls[1000001];

double get_max_y(vector<Func> &hull, int x) {
    while (hull.size() >= 2 && hull[hull.size() - 1](x) < hull[hull.size() - 2](x))
        hull.pop_back();

    return hull.back()(x);
}

void add_func(vector<Func> &hull, Func func) {
    if (hull.empty() || !func.is_inferior_to(hull.back())) {
        while (hull.size() >= 2 && func.overtaken(hull.back()) >= hull.back().overtaken(hull[hull.size() - 2]))
            hull.pop_back();

        hull.push_back(func);
    }
}

int main() {
    scan(k, N), K = k * .5;
    for (int i = 1; i <= N; i++) cache[i] = pow(i, K);

    for (int i = 1; i <= N; i++) {
        int n; scan(n);
        add_func(hulls[n], Func{ cnt[n]++, dp[i - 1] });
        dp[i] = get_max_y(hulls[n], cnt[n]);
    }

    printf("%.9lf\n", dp[N]);

    return 0;
}