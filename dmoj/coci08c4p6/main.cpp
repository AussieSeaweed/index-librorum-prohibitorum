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
#define MOD 1000000007
using namespace std;

int N, K, heights[500];
long long comb_dp[501][501];

long long comb(int n, int k) {
    if (k > n) return 0;
    if (~comb_dp[n][k]) return comb_dp[n][k];
    if (k == 0) return comb_dp[n][k] = 1;
    return comb_dp[n][k] = (comb(n - 1, k - 1) + comb(n - 1, k)) % MOD;
}

bool is_end(int l, int r, int b) {
    for (int i = l; i <= r; i++)
        if (heights[i] > b)
            return false;
    return true;
}

int get_first_split_pt(int l, int r, int b) {
    for (int i = l; i <= r; i++)
        if (heights[i] == b)
            return i;
    return -1;
}

int get_min_height(int l, int r) {
    int ret = inf;

    for (int i = l; i <= r; i++)
        ret = min(ret, heights[i]);

    return ret;
}

long long *solve(int l, int r, int b) {
    if (is_end(l, r, b)) {
        long long *ret = new long long[501];
        ret[0] = 1; fill(ret + 1, ret + 501, 0);
        return ret;
    }

    int split_pt = get_first_split_pt(l, r, b);

    if (~split_pt) {
        long long *dp1 = solve(l, split_pt - 1, b), *dp2 = solve(split_pt + 1, r, b), *ret = new long long[501];
        fill(ret, ret + 501, 0);

        for (int i = 0; i <= 500; i++)
            for (int j = 0; j <= i; j++)
                ret[i] = (ret[i] + dp1[j] * dp2[i - j]) % MOD;

        delete[] dp1;
        delete[] dp2;
        return ret;
    } else {
        int min_height = get_min_height(l, r);
        long long *dp = solve(l, r, min_height), *ret = new long long[501];
        fill(ret, ret + 501, 0);

        for (int i = 0; i <= 500; i++) {
            long long perm = 1;
            for (int j = 0; j <= i; perm = perm * (min_height - b - j) % MOD, j++) {
                ret[i] = (ret[i] + perm * comb(r - l + 1 - (i - j), j) % MOD * dp[i - j]) % MOD;
            }
        }

        delete[] dp;
        return ret;
    }
}

int main() {
    memset(comb_dp, -1, sizeof comb_dp);
    scan(N, K);
    for (int i = 0; i < N; i++) scan(heights[i]);
    printf("%lld\n", solve(0, N - 1, 0)[K]);
    return 0;
}