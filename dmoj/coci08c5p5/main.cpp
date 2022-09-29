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

long long A, B, digits[16], dp[16][10][16], cnt[16], p10[16], num[16];

long long count(int i, bool tight) {
    if (i == -1) return 1;
    if (!tight && ~cnt[i]) return cnt[i];

    long long ret = 0, lim = tight ? digits[i] : 9;

    for (int j = 0; j <= lim; j++) {
        ret += count(i - 1, tight && j == lim);
    }

    if (!tight) cnt[i] = ret;

    return ret;
}

long long solve(int i, int prev_digit, int prev_len, bool tight) {
    if (i == -1) return prev_digit * prev_len * prev_len;
    if (!tight && ~dp[i][prev_digit][prev_len]) return dp[i][prev_digit][prev_len];

    long long ret = 0, lim = tight ? digits[i] : 9;

    for (int j = 0; j <= lim; j++) {
        if (j == prev_digit)
            ret += solve(i - 1, prev_digit, prev_len + 1, tight && j == lim);
        else
            ret += prev_digit * prev_len * prev_len * count(i - 1, tight && j == lim) + solve(i - 1, j, 1, tight && j == lim);
    }

    if (!tight) dp[i][prev_digit][prev_len] = ret;

    return ret;
}

long long solve(long long a) {
    for (int i = 0; i < 16; i++)
        digits[i] = a % 10, a /= 10;

    for (int i = 0; i < 16; i++)


    return solve(15, 0, 0, true);
}

long long bf_solve(long long a) {
    int i, len, prev_digit;

    for (i = 0; i < 16; i++)
        digits[i] = a % 10, a /= 10;

    long long ret = 0;

    for (i = prev_digit = len = 0; i < 16; i++) {
        if (prev_digit != digits[i]) ret += prev_digit * len * len, len = 0;
        prev_digit = digits[i], len++;
    }

    return ret;
}

int main() {
    memset(cnt, -1, sizeof cnt);
    memset(dp, -1, sizeof dp);
    p10[0] = 1;
    for (int i = 1; i < 16; i++) p10[i] = 10 * p10[i - 1];

    scan(A);
    scan(B);
    printf("%lld\n", solve(B) - solve(A - 1));
    return 0;
}