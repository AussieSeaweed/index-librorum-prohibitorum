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
#define MOD 1000000007
using namespace std;

int N;
long long X[500000], Y[500000];
long long num[1048576], ans[1048576];
double lnum[1048576], lans[1048576];

void build(int node, int lo, int hi) {
    if (lo == hi) {
        num[node] = X[lo] % MOD;
        lnum[node] = log(X[lo]);
        ans[node] = X[lo] * Y[lo] % MOD;
        lans[node] = log(X[lo] * Y[lo]);
    } else {
        int mid = (lo + hi) / 2;
        build(node * 2, lo, mid);
        build(node * 2 + 1, mid + 1, hi);

        num[node] = num[node * 2] * num[node * 2 + 1] % MOD;
        lnum[node] = lnum[node * 2] + lnum[node * 2 + 1];

        if (lans[node * 2] < lnum[node * 2] + lans[node * 2 + 1]) {
            lans[node] = lnum[node * 2] + lans[node * 2 + 1];
            ans[node] = num[node * 2] * ans[node * 2 + 1] % MOD;
        } else {
            lans[node] = lans[node * 2];
            ans[node] = ans[node * 2];
        }
    }
}

void update(int node, int lo, int hi, int i, long long x, long long y) {
    if (i < lo || hi < i) return;

    if (lo == hi) {
        X[i] = x, Y[i] = y;
        num[node] = x % MOD;
        lnum[node] = log(x);
        ans[node] = x * y % MOD;
        lans[node] = log(x * y);
    } else {
        int mid = (lo + hi) / 2;
        update(node * 2, lo, mid, i, x, y);
        update(node * 2 + 1, mid + 1, hi, i, x, y);

        num[node] = num[node * 2] * num[node * 2 + 1] % MOD;
        lnum[node] = lnum[node * 2] + lnum[node * 2 + 1];

        if (lans[node * 2] < lnum[node * 2] + lans[node * 2 + 1]) {
            lans[node] = lnum[node * 2] + lans[node * 2 + 1];
            ans[node] = num[node * 2] * ans[node * 2 + 1] % MOD;
        } else {
            lans[node] = lans[node * 2];
            ans[node] = ans[node * 2];
        }
    }
}

int updateX(int pos, int val) {
    update(1, 0, N - 1, pos, val, Y[pos]);
    return ans[1];
}

int updateY(int pos, int val) {
    update(1, 0, N - 1, pos, X[pos], val);
    return ans[1];
}

int init(int N, int X[], int Y[]) {
    ::N = N;
    copy(X, X + N, ::X), copy(Y, Y + N, ::Y);
    build(1, 0, N - 1);
    return ans[1];
}