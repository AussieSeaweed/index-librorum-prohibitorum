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
#define MOD 998244353
using namespace std;

long long powmod(long long base, long long power) {
    long long ret = 1;
    while (power) {
        if (power & 1)
            ret = ret * base % MOD;
        base = base * base % MOD;
        power >>= 1;
    }
    return ret;
}

long long A, B, N, R, D, a[1000][1000], dp[1000][1000][2];

long long solve(int i, int j, bool dir) {
    if (~dp[i][j][dir]) return dp[i][j][dir];
    if (i == N - 1 && j == N - 1) return dp[i][j][dir] = a[i][j];
    else if (i == 0 && j == 0) return dp[i][j][dir] = (a[i][j] + R * solve(i, j + 1, true) + D * solve(i + 1, j, false)) % MOD;
    else if (j == N - 1) return dp[i][j][dir] = (a[i][j] + solve(i + 1, j, dir)) % MOD;
    else if (i == N - 1) return dp[i][j][dir] = (a[i][j] + solve(i, j + 1, dir)) % MOD;
    else if (dir) return dp[i][j][dir] = (a[i][j] + D * solve(i, j + 1, dir) + R * solve(i + 1, j, !dir)) % MOD;
    else /*if (!dir)*/ return dp[i][j][dir] = (a[i][j] + D * solve(i + 1, j, dir) + R * solve(i, j + 1, !dir)) % MOD;
}

int main() {
    scan(A);
    scan(B);
    R = A * powmod(B, MOD - 2) % MOD;
    D = (B - A) * powmod(B, MOD - 2) % MOD;
    scan(N);
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) scan(a[i][j]);
    memset(dp, -1, sizeof dp);
    printf("%lld\n", solve(0, 0, false));
    return 0;
}